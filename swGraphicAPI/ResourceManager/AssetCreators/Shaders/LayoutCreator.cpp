/**
@file ShaderCreator.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "LayoutCreator.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"



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
ResourceObject*		LayoutCreator::LoadFromRaw		( const filesystem::Path& assetName, const BufferRaw& rawData )
{
	assert( !"InputLayout is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw			LayoutCreator::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw			LayoutCreator::SaveToRaw		( ResourcePtr< ResourceObject > resource )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
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
