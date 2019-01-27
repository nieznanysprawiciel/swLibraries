/**
@file LinearGradientBrush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/stdafx.h"
#include "LinearGradientBrush.h"



namespace sw {
namespace gui
{

// ================================ //
//
LinearGradientBrush::LinearGradientBrush()
	:	GradientBrush( LinearGradientBrush::ConstantsSize() )
{}


// ================================ //
//
BufferRange			LinearGradientBrush::BufferData			()
{
	return PrepareBuffer( m_constants.GetView() );
}

// ================================ //
//
std::string			LinearGradientBrush::ShaderFunctionFile	()
{
	return "$(CoreGUI-Shader-Dir)/Brush/LinearGradientBrush.psh";
}

// ================================ //
//
Size				LinearGradientBrush::ConstantsSize		() const
{
	return sizeof( m_constants );
}


}	// gui
}	// sw