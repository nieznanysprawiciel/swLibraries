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
BufferRange				SolidColorBrush::BufferData			()
{
	return m_constants.GetView();
}

// ================================ //
//
std::string				SolidColorBrush::ShaderFunctionFile	()
{
	return "$(CoreGUI-Shader-Dir)/Brush/SolidColorBrush.psh";
}

// ================================ //
//
std::wstring			SolidColorBrush::TextureSource		()
{
	// Brush doesn't use textures.
	return L"";
}

// ================================ //
//
std::wstring			SolidColorBrush::ConstantsName		()
{
	return L"sw::gui::SolidColorBrush::CB";
}

}	// gui
}	// sw
