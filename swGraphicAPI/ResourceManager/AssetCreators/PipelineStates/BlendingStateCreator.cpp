/**
@file BlendingStateCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "BlendingStateCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"
#include "swCommonLib/Common/Converters.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"


namespace sw
{

// ================================ //
//
Nullable< Resource* >		BlendingStateCreator::Create		( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	TypeID type = createInfo.get_type();
	if( type == TypeID::get< BlendingInfo >() )
		return ResourcesFactory::CreateBlendingState( static_cast< BlendingInfo& >( createInfo ) );

	return "[BlendingStateCreator] IAssetCreateInfo of type [" + type.get_name().to_string() + "] not supported.";
}

// ================================ //
//
Nullable< Resource* >		BlendingStateCreator::LoadFromRaw	( const filesystem::Path& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					BlendingStateCreator::SaveToRaw	( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					BlendingStateCreator::SaveToRaw	( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						BlendingStateCreator::IsCacheable	() const
{
	return false;
}

// ================================ //
//
bool						BlendingStateCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						BlendingStateCreator::GetAssetType	() const
{
	return TypeID::get< BlendingState >();
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//



}	// sw
