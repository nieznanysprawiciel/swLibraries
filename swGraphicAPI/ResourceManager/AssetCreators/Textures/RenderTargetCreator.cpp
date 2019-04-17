/**
@file RenderTargetCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "RenderTargetCreator.h"

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/Buffers/BufferTyped.h"

#include "swGraphicAPI/Resources/Textures/RenderTarget.h"

#include "MipMapGenerator.h"


namespace sw
{

// ================================ //
//
Nullable< Resource* >		RenderTargetCreator::Create		( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();
	if( type == TypeID::get< RenderTargetDescriptor >() )
	{
		return ResourcesFactory::CreateRenderTarget( assetName, static_cast< RenderTargetDescriptor& >( createInfo ) );
	}

	return "[RenderTargetCreator] IAssetCreateInfo of type [" + TypeID::get( createInfo ).get_name().to_string() + "] not supported.";
}

// ================================ //
//
Nullable< Resource* >		RenderTargetCreator::LoadFromRaw	( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					RenderTargetCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					RenderTargetCreator::SaveToRaw	( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						RenderTargetCreator::IsCacheable	() const
{
	return false;
}

// ================================ //
//
bool						RenderTargetCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						RenderTargetCreator::GetAssetType	() const
{
	return TypeID::get< RenderTarget >();
}



}	// sw
