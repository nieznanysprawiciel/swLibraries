/**
@file ImageBrush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/stdafx.h"
#include "ImageBrush.h"



namespace sw {
namespace gui
{

// ================================ //
//
ImageBrush::ImageBrush()
    : ImageBrush( AssetPath() )
{}

// ================================ //
//
ImageBrush::ImageBrush( AssetPath tex )
    :   Brush( ConstantBufferMode::Enable )
    ,   m_textureSource( std::move( tex ) )
{
    Rect region;
    region.Left = 0.0f;
    region.Top = 1.0f;
    region.Right = 1.0f;
    region.Bottom = 0.0f;

    m_constants.TextureRegion = region;
    m_constants.Stretch = Stretch::Fill;
}

// ================================ //
//
BufferRange				ImageBrush::BufferData			()
{
    return m_constants.GetView();
}

// ================================ //
//
filesystem::Path        ImageBrush::ShaderFunctionFile	()
{
    return "$(CoreGUI-Shader-Dir)/Brush/ImageBrush.psh";
}

// ================================ //
//
AssetPath   			ImageBrush::TextureSource		()
{
    // Brush doesn't use textures.
    return m_textureSource;
}

// ================================ //
//
AssetPath   			ImageBrush::ConstantsName		()
{
    return "::sw::gui::ImageBrush::CB";
}

}	// gui
}	// sw