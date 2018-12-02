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
Geometry::Geometry		( bool sharedBuffer )
	:	m_sharedBuffer( sharedBuffer )
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

