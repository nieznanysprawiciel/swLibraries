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
{
	m_constants.GradientStart = Position( 0.5f, 0.0f );
	m_constants.GradientEnd = Position( 0.5f, 1.0f );
}


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
void				LinearGradientBrush::SetGradientAxis	( Point start, Point end )
{
	m_constants.GradientStart = start;
	m_constants.GradientEnd = end;

	InvalidateConstants();
}

// ================================ //
//
Size				LinearGradientBrush::ConstantsSize		() const
{
	return sizeof( m_constants );
}


}	// gui
}	// sw