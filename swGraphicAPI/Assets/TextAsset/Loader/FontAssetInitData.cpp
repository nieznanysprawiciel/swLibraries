/**
@file FontAssetInitData.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/TextAsset/stdafx.h"


#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"

#include "FontAssetInitData.h"

#include <algorithm>


namespace sw
{

std::wstring            FontLoaderData::DefaultCharacterSet()
{
    return std::wstring( L"1234568790.~,/?ìë:;[]{}\\|`!@#$%^&*()-_+=<>ñ∞\"'abcdefghijklmnopqrstuvxyzπÍÊüø≥úÛÒwABCDEFGHIJKLMNOPQRSTUVXYZ• ∆èØ£å”—Wƒ÷‹äé«…ÀŒ‘©" );
}

TypeID                  FontLoaderData::GetAssetType    () const { return TypeID::get< FontAsset >(); }
TypeID                  FontInitData::GetAssetType      () const { return TypeID::get< FontAsset >(); }

uint32                  FontLayout::GetMaxHeight() const
{
    auto max = std::max_element( this->Glyphs.begin(), this->Glyphs.end(), []( const auto& a, const auto& b ) { return a.second.Height < b.second.Height; } );
    return (*max).second.Height;
}

uint32                  FontLayout::GetMaxWidth() const
{
    auto max = std::max_element( this->Glyphs.begin(), this->Glyphs.end(), []( const auto& a, const auto& b ) { return a.second.Width < b.second.Width; } );
    return (*max).second.Width;
}

}	// sw

