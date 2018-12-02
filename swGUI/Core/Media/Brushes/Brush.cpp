/**
@file Brush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"



#include "Brush.h"



namespace sw {
namespace gui
{

// ================================ //
//
Brush::Brush		( EnableConstantBuffer enableCB )
	:	m_useConstantBuffer( enableCB == EnableConstantBuffer::True )
	,	m_invalidateConstants( false )
	,	m_invalidateTexture( false )
{
	InvalidateShader();
}


// ================================ //
//
void			Brush::InvalidateConstants		()
{
	m_invalidateConstants = true;
}

// ================================ //
//
void			Brush::InvalidateShader			()
{
	m_invalidateShader = true;
}

// ================================ //
//
void			Brush::InvalidateTexture		()
{
	m_invalidateTexture = true;
}

// ================================ //
//
void			Brush::ShaderUpdated			()
{
	m_invalidateShader = false;
}

// ================================ //
//
void			Brush::TextureUpdated			()
{
	m_invalidateTexture = false;
}

// ================================ //
//
void			Brush::ConstantsUpdated			()
{
	m_invalidateConstants = false;
}

}	// gui
}	// sw