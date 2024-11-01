/**
@file FontAssetInitData.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "swCommonLib/Common/fmt.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"

#include "FontAssetInitData.h"

#include <algorithm>


namespace sw
{

// ================================ //
// 

std::wstring            FontLoaderData::DefaultCharacterSet()
{
    return std::wstring( L"1234568790.~,/?ìë:;[]{}\\|`!@#$%^&*()-_+=<>ñ∞\"'abcdefghijklmnopqrstuvxyzπÍÊüø≥úÛÒwABCDEFGHIJKLMNOPQRSTUVXYZ• ∆èØ£å”—Wƒ÷‹äé«…ÀŒ‘©" );
}

TypeID                  FontLoaderData::GetAssetType    () const { return TypeID::get< FontAsset >(); }

// ================================ //
// 

std::string             FontLoaderData::ResourceKey() const
{
    return fmt::format( "/Font?fontSize={},genMipMaps={}", this->FontSize, this->GenerateMipmaps );
}

TypeID                  FontInitData::GetAssetType      () const { return TypeID::get< FontAsset >(); }

// ================================ //
// 

std::string             FontInitData::ResourceKey() const
{
    return fmt::format( "/Font?fontSize={},genMipMaps={}", this->FontSize, this->FontAtlas->GetDescriptor().GenerateMipMaps );
}

// ================================ //
// 

uint32                  FontLayout::GetMaxHeight() const
{
    auto max = std::max_element( this->Glyphs.begin(), this->Glyphs.end(), []( const auto& a, const auto& b ) { return a.second.Height < b.second.Height; } );
    return (*max).second.Height;
}

// ================================ //
// 

uint32                  FontLayout::GetMaxWidth() const
{
    auto max = std::max_element( this->Glyphs.begin(), this->Glyphs.end(), []( const auto& a, const auto& b ) { return a.second.Width < b.second.Width; } );
    return (*max).second.Width;
}

// ================================ //
// 

uint32                  FontLayout::GetMaxHeightWithPadding() const
{
    return GetMaxHeight() + 2*Padding;
}

// ================================ //
// 

uint32                  FontLayout::GetMaxWidthWithPadding() const
{
    return GetMaxWidth() + 2 * Padding;
}

// ================================ //
// 

ImageRect               FontLayout::GetGlyphCoords( wchar_t character ) const
{
    auto iter = this->Glyphs.find( character );
    if( iter != this->Glyphs.end() )
        return iter->second.GetGlyphCoords();

    return ImageRect{ 0, 0, 0, 0 };
}

}	// sw

