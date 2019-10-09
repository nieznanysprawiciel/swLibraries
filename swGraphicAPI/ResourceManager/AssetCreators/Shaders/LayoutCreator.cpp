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
Nullable< Resource* >		LayoutCreator::Create			( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
    TypeID type = createInfo.get_type();
    if( type == TypeID::get< InputLayoutDescriptor >() )
    {
        auto init = static_cast< InputLayoutDescriptor&& >( createInfo );
        return ResourcesFactory::CreateInputLayout( assetName, init );
    }

    return fmt::format( "[LayoutCreator] IAssetCreateInfo of type [{}] not supported.", type );
}

// ================================ //
//
Nullable< Resource* >		LayoutCreator::LoadFromRaw		( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"InputLayout is not cacheable" );
	return nullptr;
}

// ================================ //
//
BufferRaw					LayoutCreator::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
BufferRaw					LayoutCreator::SaveToRaw		( ResourcePtr< Resource > resource )
{
	assert( !"InputLayout is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
bool						LayoutCreator::IsCacheable		() const
{
	return false;
}

// ================================ //
//
bool						LayoutCreator::SupportsResourceToRaw() const
{
	return false;
}

// ================================ //
//
TypeID						LayoutCreator::GetAssetType			() const
{
	return TypeID::get< ShaderInputLayout >();
}



}	// sw
