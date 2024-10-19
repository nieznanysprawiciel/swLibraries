/**
@file BufferCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "BufferCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/Common/fmt.h"



namespace sw
{

// ================================ //
//
Nullable< Resource* >	BufferCreator::Create		( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();
	if( type == TypeID::get< ConstantBufferInitData >() )
		return CreateConstantsBuffer( assetName, static_cast< ConstantBufferInitData& >( createInfo ) );
	else if( type == TypeID::get< VertexBufferInitData >() )
		return CreateVertexBuffer( assetName, static_cast< VertexBufferInitData& >( createInfo ) );
	else if( type == TypeID::get< IndexBufferInitData >() )
		return CreateIndexBuffer( assetName, static_cast< IndexBufferInitData& >( createInfo ) );

    return fmt::format( "[BufferCreator] IAssetCreateInfo of type [{}] not supported.", type );
}

// ================================ //
//
Nullable< Resource* >	BufferCreator::LoadFromRaw	( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					BufferCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					BufferCreator::SaveToRaw	( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						BufferCreator::IsCacheable	() const
{
	return false;
}

// ================================ //
//
bool						BufferCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						BufferCreator::GetAssetType	() const
{
	return TypeID::get< Buffer >();
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//


// ================================ //
//
Nullable< Buffer* >			BufferCreator::CreateVertexBuffer		( const AssetPath& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount )
{
	VertexBufferInitData initData;
	initData.Data = buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;
	
	return CreateVertexBuffer( name, initData );
}

// ================================ //
//
Nullable< Buffer* >			BufferCreator::CreateVertexBuffer		( const AssetPath& name, const VertexBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name, data.Data, data.CreateBufferInfo() );
}

// ================================ //
//
Nullable< Buffer* >			BufferCreator::CreateIndexBuffer		( const AssetPath& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount )
{
	IndexBufferInitData initData;
	initData.Data = buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;

	return CreateIndexBuffer( name, initData );
}

// ================================ //
//
Nullable< Buffer* >			BufferCreator::CreateIndexBuffer		( const AssetPath& name, const IndexBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name, data.Data, data.CreateBufferInfo() );
}

// ================================ //
//
Nullable< Buffer* >			BufferCreator::CreateConstantsBuffer	( const AssetPath& name, const uint8* buffer, unsigned int size )
{
	ConstantBufferInitData initData;
	initData.Data = (const uint8*)buffer;
	initData.ElementSize = size;
	initData.NumElements = 1;

	return CreateConstantsBuffer( name, initData );
}

// ================================ //
//
Nullable< Buffer* >			BufferCreator::CreateConstantsBuffer	( const AssetPath& name, const ConstantBufferInitData& data )
{
	if( data.ElementSize % 16 != 0 )
		return fmt::format( "[BufferCreator] Invalid Buffer size={}. Should be multiply of 16.", data.ElementSize );

	return ResourcesFactory::CreateBufferFromMemory( name, data.Data, data.CreateBufferInfo() );
}


}	// sw
