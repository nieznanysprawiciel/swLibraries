/**
@file AngleGradientBrush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/stdafx.h"
#include "AngleGradientBrush.h"



namespace sw {
namespace gui
{

// ================================ //
//
AngleGradientBrush::AngleGradientBrush()
    : GradientBrush( AngleGradientBrush::ConstantsSize() )
{
    m_constants.GradientCenter = Position( 0.5f, 0.5f );
}


// ================================ //
//
BufferRange			AngleGradientBrush::BufferData			()
{
    return PrepareBuffer( m_constants.GetView() );
}

// ================================ //
//
filesystem::Path	AngleGradientBrush::ShaderFunctionFile	()
{
    return "$(CoreGUI-Shader-Dir)/Brush/AngleGradientBrush.psh";
}

// ================================ //
//
void				AngleGradientBrush::SetGradientCenter	( Point center )
{
    m_constants.GradientCenter = center;

    InvalidateConstants();
}

// ================================ //
//
Size				AngleGradientBrush::ConstantsSize		() const
{
    return sizeof( m_constants );
}


}	// gui
}	// sw