/**
@file FontCreator.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "FontAssetCreator.h"

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{

// ================================ //
//
Nullable< Resource* >	    FontCreator::Create		    ( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
    TypeID type = createInfo.get_type();
    if( type == TypeID::get< FontInitData >() )
    {
        return new FontAsset( assetName, std::move( static_cast< FontInitData&& >( createInfo ) ) );
    }

    return "[FontCreator] IAssetCreateInfo of type [" + TypeID::get( createInfo ).get_name().to_string() + "] not supported.";
}

// ================================ //
//
Nullable< Resource* >	    FontCreator::LoadFromRaw	( const AssetPath& assetName, const BufferRaw& rawData )
{
    assert( !"Buffer is not cacheable" );
    return nullptr;
}

// ================================ //
//
BufferRaw					FontCreator::SaveToRaw	    ( const IAssetCreateInfo& createInfo )
{
    assert( !"Buffer is not cacheable" );
    return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					FontCreator::SaveToRaw	    ( ResourcePtr< Resource > resource )
{
    assert( !"Buffer is not cacheable" );
    return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						FontCreator::IsCacheable	            () const
{
    return false;
}

// ================================ //
//
bool						FontCreator::SupportsResourceToRaw      () const
{
    return false;
}

// ================================ //
//
TypeID						FontCreator::GetAssetType	            () const
{
    return TypeID::get< FontAsset >();
}

// ================================ //
//
FontCreatorPtr			FontCreator::CreateCreator			()
{
    return std::make_shared< FontCreator >();
}


}	// sw
