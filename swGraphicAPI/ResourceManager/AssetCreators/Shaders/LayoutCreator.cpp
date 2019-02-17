/**
@file ShaderCreator.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "LayoutCreator.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"


namespace sw
{

// ================================ //
//
ResourceObject*		LayoutCreator::Create			( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	auto init = static_cast< InputLayoutDescriptor* >( &createInfo );


	return nullptr;
}

// ================================ //
//
ResourceObject*		LayoutCreator::LoadFromRaw		( const filesystem::Path& assetName, const MemoryChunk& rawData )
{
	assert( !"InputLayout is not cacheable" );
	return nullptr;
}

// ================================ //
//
MemoryChunk			LayoutCreator::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"InputLayout is not cacheable" );
	return MemoryChunk();
}

// ================================ //
//
MemoryChunk			LayoutCreator::SaveToRaw		( ResourcePtr< ResourceObject > resource )
{
	assert( !"InputLayout is not cacheable" );
	return MemoryChunk();
}

// ================================ //
//
bool				LayoutCreator::SupportsResourceToRaw()
{
	return false;
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//



}	// sw
