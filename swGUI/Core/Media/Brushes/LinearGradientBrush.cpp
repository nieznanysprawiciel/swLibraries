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
LinearGradient::LinearGradient()
	:	GradientBrush( LinearGradient::ConstantsSize() )
{}


// ================================ //
//
BufferRange			LinearGradient::BufferData			()
{
	return PrepareBuffer( m_constants.GetView() );
}

// ================================ //
//
std::string			LinearGradient::ShaderFunctionFile	()
{
	return std::string();
}

// ================================ //
//
Size				LinearGradient::ConstantsSize		() const
{
	return sizeof( m_constants );
}


}	// gui
}	// sw