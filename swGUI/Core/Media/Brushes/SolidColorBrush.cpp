/**
@file SolidColorBrush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "SolidColorBrush.h"



namespace sw {
namespace gui
{

// ================================ //
//
SolidColorBrush::SolidColorBrush()
	:	Brush( Brush::ConstantBufferMode::Enable )
{}

// ================================ //
//
SolidColorBrush::SolidColorBrush( const Color& color )
	:	Brush( Brush::ConstantBufferMode::Enable )
{
	m_constants.Color = color;
}


// ================================ //
//
BufferRange				SolidColorBrush::BufferData			()
{
	return m_constants.GetView();
}

// ================================ //
//
filesystem::Path        SolidColorBrush::ShaderFunctionFile	()
{
	return "$(CoreGUI-Shader-Dir)/Brush/SolidColorBrush.psh";
}

// ================================ //
//
AssetPath   			SolidColorBrush::TextureSource		()
{
	// Brush doesn't use textures.
	return "";
}

// ================================ //
//
AssetPath   			SolidColorBrush::ConstantsName		()
{
	return "::sw::gui::SolidColorBrush::CB";
}

}	// gui
}	// sw
