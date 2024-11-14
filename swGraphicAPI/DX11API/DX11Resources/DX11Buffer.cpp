/**
@file DX11Buffer.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11Buffer.h"
#include "DX11Initializer/DX11ConstantsMapper.h"
#include "swGraphicAPI/DX11API/DX11Initializer/DX11Utils.h"

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/fmt.h"

#include <limits>



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11Buffer >( "sw::DX11Buffer" );
}


namespace sw
{

// ================================ //
//
DX11Buffer::DX11Buffer			( const AssetPath& name, const BufferInfo& descriptor, ID3D11Buffer* buff )
	: Buffer( name, descriptor.ElementSize, descriptor.NumElements ), m_buffer( buff )
	, m_descriptor( descriptor )
{
	if( IsDebugLayerEnabled() )
	{
		std::string nameStr = name.String();
		SetDebugName( m_buffer.Get(), nameStr );
	}
}

// ================================ //
//
DX11Buffer::~DX11Buffer()
{
	m_buffer = nullptr;
}


// ================================ //
//
sw::Nullable< Buffer* >				DX11Buffer::CreateFromMemory	( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo )
{
	ResourceBinding bindFlag;
	if( bufferInfo.BufferType == BufferType::VertexBuffer )
		bindFlag = ResourceBinding::RB_VertexBuffer;
	else if( bufferInfo.BufferType == BufferType::IndexBuffer )
		bindFlag = ResourceBinding::RB_IndexBuffer;
	else if( bufferInfo.BufferType == BufferType::ConstantBuffer )
		bindFlag = ResourceBinding::RB_ConstantsBuffer;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = DX11ConstantsMapper::Get( bufferInfo.Usage );
	bufferDesc.BindFlags = DX11ConstantsMapper::Get( bindFlag );
	bufferDesc.ByteWidth = bufferInfo.NumElements * bufferInfo.ElementSize;

	D3D11_SUBRESOURCE_DATA* initDataPtr = nullptr;
	D3D11_SUBRESOURCE_DATA initData;
	if( data )
	{
		// If the buffer does not exist, we should pass nullptr to the buffer creation function.
		ZeroMemory( &initData, sizeof( initData ) );
		initData.pSysMem = data;
		initDataPtr = &initData;
	}

	HRESULT result;
	ID3D11Buffer* newBuffer;
	result = device->CreateBuffer( &bufferDesc, initDataPtr, &newBuffer );
	if( FAILED( result ) )
        return fmt::format( "[DX11Buffer] Buffer creation failed. {}", DX11Utils::ErrorString( result ) );

	DX11Buffer* newBufferObject = new DX11Buffer( name, bufferInfo, newBuffer );
	return newBufferObject;
}

/**@brief Copies the buffer memory and returns it in a MemoryChunk.

The function returns the buffer content. The memory is copied twice.
First to a temporary buffer on the GPU, and then after mapping to RAM,
it is copied to a MemoryChunk.

@todo It would not be necessary to perform copying on the GPU if the buffer was created with the flags
D3D11_USAGE_STAGING or D3D11_USAGE_DEFAULT. The flags need to be checked and copying should be done only when necessary.

@attention The function is not suitable for multithreading. It uses DeviceContext for copying data,
therefore it requires synchronization with other rendering functions.
@todo Maybe function should take Renderer as a parameter than?*/
MemoryChunk									DX11Buffer::CopyData()
{
	// Trzeba stworzy� nowy bufor
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_STAGING;
	//bufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;		// With usage::staging flag, the resource cannot be bound to the graphics pipeline.
	bufferDesc.ByteWidth = m_elementSize * m_elementCount;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

	HRESULT result;
	ID3D11Buffer* newBuffer;
	result = device->CreateBuffer( &bufferDesc, nullptr, &newBuffer );
	if( FAILED( result ) )
		return MemoryChunk();

	// Copying the contents between buffers
	device_context->CopyResource( newBuffer, m_buffer.Get() );

	D3D11_MAPPED_SUBRESOURCE data;
	result = device_context->Map( newBuffer, 0, D3D11_MAP::D3D11_MAP_READ, 0, &data );
	if( FAILED( result ) )
		return MemoryChunk();

	MemoryChunk memoryChunk;
	memoryChunk.MemoryCopy( (int8*)data.pData, m_elementSize * m_elementCount );

	device_context->Unmap( newBuffer, 0 );
	newBuffer->Release();

	return std::move( memoryChunk );
}

// ================================ //

ReturnResult			DX11Buffer::UpdateData( BufferRange data, PtrOffset offset )
{
    // Buffer must be updatable.
    if( m_descriptor.Usage == ResourceUsage::Static || m_descriptor.Usage == ResourceUsage::Staging )
        return fmt::format( "Buffer not updatable. Create with ResourceUsage Default or Dynamic. (Current: {})",
                            Convert::ToString( m_descriptor.Usage ) );

	auto bufferSize = m_elementSize * m_elementCount;
    if( offset + data.DataSize > bufferSize )
        return fmt::format( "Update: Data size exceeds Buffer size. Buffer size: {}, Data size: {}, Offset: {}", bufferSize,
                            data.DataSize, offset );

    if( m_descriptor.Usage == ResourceUsage::Dynamic )
    {
        D3D11_MAPPED_SUBRESOURCE updateData;
        HRESULT result = device_context->Map( m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &updateData );
        if( SUCCEEDED( result ) )
        {
            memcpy( (uint8*)updateData.pData + offset, data.DataPtr, data.DataSize );
            device_context->Unmap( m_buffer.Get(), 0 );

            return Success::True;
        }
        else
            return fmt::format( "Failed to map Buffer: {}", DX11Utils::ErrorString( result ) );
    }
    else
    {
        // ResourceUsage::Default
        D3D11_BOX destRegion;
        destRegion.left = (UINT)offset;
        destRegion.right = (UINT)( data.DataSize + offset );
        destRegion.top = 0;
        destRegion.bottom = 0;
        destRegion.front = 0;
        destRegion.back = 0;

        device_context->UpdateSubresource( m_buffer.Get(), 0, &destRegion, data.DataPtr, 0, 0 );
        return Success::True;
    }

    return Success::True;
}

// ================================ //

ReturnResult			DX11Buffer::Resize( BufferRange newData )
{
    auto bufferSize = m_elementSize * m_elementCount;
	if( newData.DataSize <= bufferSize )
	{
		// No need to resize. TODO: consider if we shoudl ever scale buffers down.
        return UpdateData( newData, 0 );
	}

	if( newData.DataSize / m_elementSize > std::numeric_limits< uint32 >::max() )
        return "Expected size exceeds maximum Buffer element count.";
	
	BufferInfo newDesc = m_descriptor;
    newDesc.NumElements = uint32( newData.DataSize / m_elementSize );

	auto result = DX11Buffer::CreateFromMemory( GetAssetPath(), newData.DataPtr, newDesc );
    ReturnIfInvalid( result );

	// Replacing pointer should automatically release the old Buffer.
	m_buffer = static_cast< DX11Buffer* >( result.Get() )->Get();
    m_descriptor = newDesc;

    return Success::True;
}


}	// sw

