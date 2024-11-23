/**
@file Brush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"



#include "Brush.h"
#include "swGUI/Core/Media/Geometry/Geometry.h"



namespace sw {
namespace gui
{

// ================================ //
//
Brush::Brush		( ConstantBufferMode enableCB )
	:	m_useConstantBuffer( enableCB == ConstantBufferMode::Enable )
{
	InvalidateShader();
}


// ================================ //
//
void			Brush::InvalidateConstants		()
{
    m_constantsState.Invalidate();
}

// ================================ //
//
void			Brush::InvalidateShader			()
{
    m_shaderState.Invalidate();
}

// ================================ //
//
void			Brush::InvalidateTexture		()
{
    m_textureState.Invalidate();
}

// ================================ //
//
void			Brush::ShaderUpdated			( UpdateTracker16& tracker )
{
    tracker.Synchronize( m_shaderState );
}

// ================================ //
//
void			Brush::TextureUpdated			( UpdateTracker16& tracker )
{
    tracker.Synchronize( m_textureState );
}

// ================================ //
//
void			Brush::ConstantsUpdated			( UpdateTracker16& tracker )
{
    tracker.Synchronize( m_constantsState );
}


}	// gui
}	// sw