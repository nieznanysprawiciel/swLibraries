/**
@file TextureCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "TextureCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"
#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"



namespace sw
{

// ================================ //
//
Nullable< Resource* >		TextureCreator::Create		( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();


	return "[TextureCreator] IAssetCreateInfo of type [" + TypeID::get( createInfo ).get_name().to_string() + "] not supported.";
}

// ================================ //
//
Nullable< Resource* >		TextureCreator::LoadFromRaw	( const filesystem::Path& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					TextureCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					TextureCreator::SaveToRaw	( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						TextureCreator::IsCacheable	() const
{
	return false;
}

// ================================ //
//
bool						TextureCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						TextureCreator::GetAssetType	() const
{
	return TypeID::get< Texture >();
}



}	// sw
