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



namespace sw
{

// ================================ //
//
Nullable< Resource* >	BufferCreator::Create		( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();
	if( type == TypeID::get< ConstantBufferInitData >() )
		return CreateConstantsBuffer( assetName, static_cast< ConstantBufferInitData& >( createInfo ) );
	else if( type == TypeID::get< VertexBufferInitData >() )
		return CreateVertexBuffer( assetName, static_cast< VertexBufferInitData& >( createInfo ) );
	else if( type == TypeID::get< IndexBufferInitData >() )
		return CreateIndexBuffer( assetName, static_cast< IndexBufferInitData& >( createInfo ) );

	return "[BufferCreator] IAssetCreateInfo of type [" + TypeID::get( createInfo ).get_name().to_string() + "] not supported.";
}

// ================================ //
//
Nullable< Resource* >	BufferCreator::LoadFromRaw	( const filesystem::Path& assetName, const BufferRaw& rawData )
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
	return TypeID::get< BufferObject >();
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//


// ================================ //
//
Nullable< BufferObject* >			BufferCreator::CreateVertexBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount )
{
	VertexBufferInitData initData;
	initData.Data = buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;
	
	return CreateVertexBuffer( name, initData );
}

// ================================ //
//
Nullable< BufferObject* >			BufferCreator::CreateVertexBuffer		( const filesystem::Path& name, const VertexBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name.WString(), data.Data, data.CreateBufferInfo() );
}

// ================================ //
//
Nullable< BufferObject* >			BufferCreator::CreateIndexBuffer		( const filesystem::Path& name, const uint8* buffer, unsigned int elementSize, unsigned int vertCount )
{
	IndexBufferInitData initData;
	initData.Data = buffer;
	initData.ElementSize = elementSize;
	initData.NumElements = vertCount;

	return CreateIndexBuffer( name, initData );
}

// ================================ //
//
Nullable< BufferObject* >			BufferCreator::CreateIndexBuffer		( const filesystem::Path& name, const IndexBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name.WString(), data.Data, data.CreateBufferInfo() );
}

// ================================ //
//
Nullable< BufferObject* >			BufferCreator::CreateConstantsBuffer	( const filesystem::Path& name, const uint8* buffer, unsigned int size )
{
	ConstantBufferInitData initData;
	initData.Data = (const uint8*)buffer;
	initData.ElementSize = size;
	initData.NumElements = 1;

	return CreateConstantsBuffer( name, initData );
}

// ================================ //
//
Nullable< BufferObject* >			BufferCreator::CreateConstantsBuffer	( const filesystem::Path& name, const ConstantBufferInitData& data )
{
	return ResourcesFactory::CreateBufferFromMemory( name.WString(), data.Data, data.CreateBufferInfo() );
}


}	// sw
