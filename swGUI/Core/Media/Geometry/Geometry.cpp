/**
@file Geometry.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"



#include "Geometry.h"





namespace sw {
namespace gui
{


// ================================ //
//
Geometry::Geometry		( ConstantBufferMode cbMode )
	:	m_sharedBuffer( cbMode == ConstantBufferMode::UseShared )
	,	m_useConstantBuffer( cbMode != ConstantBufferMode::Disable )
    ,   m_invalidateGeometry( true )
    ,   m_invalidateConstants( true )
    ,   m_invalidateShader( true )
{}


// ================================ //
//
void			Geometry::InvalidateGeometry		()
{
	m_invalidateGeometry = true;
}

// ================================ //
//
void			Geometry::InvalidateConstants		()
{
	m_invalidateConstants = true;
}

// ================================ //
//
void			Geometry::InvalidateShader			()
{
	m_invalidateShader = true;
}

// ================================ //
//
void			Geometry::ShaderUpdated				()
{
	m_invalidateShader = false;
}

// ================================ //
//
void			Geometry::GeometryUpdated			()
{
	m_invalidateGeometry = false;
}

// ================================ //
//
void			Geometry::ConstantsUpdated			()
{
	m_invalidateConstants = false;
}


}	// gui
}	// sw

