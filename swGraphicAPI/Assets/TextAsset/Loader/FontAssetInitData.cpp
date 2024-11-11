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
    // Convert assumes that string is utf8 encoded.
    std::string_view charset = { "1234568790.~,/?“‘:;[]{}\\|`!@#$%^&*()-_+=<>–°\"'abcdefghijklmnopqrstuvxyząęćźżłśóńwABCDEFGHIJKLMNOPQRSTUVXYZĄĘĆŹŻŁŚÓŃWÄÖÜŠŽÇÉËÎÔ©" };
    return Convert::FromString< std::wstring >( charset ).Get();
}

// ================================ //
//

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

uint32                  FontLayout::GetMaxBearingY() const
{
    auto max = std::max_element( this->Glyphs.begin(), this->Glyphs.end(),
                                 []( const auto& a, const auto& b ) { return a.second.BearingY < b.second.BearingY; } );
    return ( *max ).second.BearingY;
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

// ================================ //
// Computing space character size
// Space width should be get form : https://www.mail-archive.com/freetype@nongnu.org/msg01384.html
float           FontLayout::SpaceWidth() const { return (float)Glyphs.at( L'0' ).AdvanceX; }

// ================================ //

float           FontLayout::NewLineSize() const { return (float)Glyphs.at( L'0' ).Height; }

}	// sw
