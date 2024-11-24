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
{}


// ================================ //
//
void			Geometry::InvalidateGeometry		()
{
    m_geometryState.Invalidate();
}

// ================================ //
//
void			Geometry::InvalidateConstants		()
{
    m_constantsState.Invalidate();
}

// ================================ //
//
void			Geometry::InvalidateShader			()
{
    m_shaderState.Invalidate();
}

// ================================ //
//
void			Geometry::ShaderUpdated				( UpdateTracker16& tracker )
{
    tracker.Synchronize( m_shaderState );
}

// ================================ //
//
void			Geometry::GeometryUpdated			( UpdateTracker16& tracker )
{
    tracker.Synchronize( m_geometryState );
}

// ================================ //
//
void			Geometry::ConstantsUpdated			( UpdateTracker16& tracker )
{
    tracker.Synchronize( m_constantsState );
}


}	// gui
}	// sw

