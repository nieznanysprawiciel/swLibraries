/**
@file EllipseGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "EllipseGeometry.h"

#include "swGeometrics/BasicShapes/Shapes2D/EllipseWithBorder.h"
#include "swGeometrics/BasicShapes/CoordsUV/PlanarUV.h"
#include "swGeometrics/GeometricsCore/Generators/Generator.h"
#include "swGeometrics/GeometricsCore/Processors/Transform/Translate2D.h"

#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"
#include "swCommonLib/Common/Buffers/IndexedGeometryBuffer.h"

#include "swCommonLib/Common/fmt.h"



namespace sw {
namespace gui
{

// ================================ //
//
EllipseGeometry::EllipseGeometry()
	:	Geometry( Geometry::ConstantBufferMode::Disable )
{}

// ================================ //
//
void				EllipseGeometry::SetWidth			( float width )
{
	m_width = width;
	InvalidateGeometry();
}

// ================================ //
//
void				EllipseGeometry::SetHeight		( float height )
{
	m_height = height;
	InvalidateGeometry();
}

// ================================ //
//
void				EllipseGeometry::SetThickness		( float thickness )
{
	m_strokeThickness = thickness;
	InvalidateGeometry();
}

// ================================ //
//
bool				EllipseGeometry::HitTest			( const Point& point )
{
	if( pow( point.x / ( m_width / 2.0f ), 2 ) + pow( point.y / ( m_height / 2.0f ), 2 ) < 1.0f )
		return true;

	return false;
}

// ================================ //
//
bool				EllipseGeometry::HitTest			( const Rect& rectangle )
{
	assert( !"Implement me" );
	return false;
}

// ================================ //
//
GeometryData		EllipseGeometry::Generate			()
{
	geom::EllipseWithBorder< VertexShape2D, Index16 > ellipse;
	ellipse.Width = m_width;
	ellipse.Height = m_height;
	ellipse.StrokeThickness = m_strokeThickness;
	ellipse.Tesselation = uint32( m_width + m_height ) / 4;			// Estimate tesselation based on ellipse size.

	geom::PlanarUV< VertexShape2D > planarUV;
	planarUV.MinX = 0.0f;
	planarUV.MinY = -m_height;
	planarUV.MaxX = m_width;
	planarUV.MaxY = 0.0f;

	auto geometry = geom::Generate< geom::IndexedGeometryBuffer< VertexShape2D, Index16 > >( ellipse, geom::Translate2D< VertexShape2D >( m_width / 2, -m_height / 2 ), planarUV );
	/// @todo Error handling or logging.

	GeometryData geomData( geometry.Get().Verticies.MoveToRawBuffer(), geometry.Get().Indicies.MoveToRawBuffer() );
	geomData.FillIdxEnd = (uint32)ellipse.GetNumberFillIndicies();
	geomData.BorderIdxEnd = (uint32)ellipse.GetNumberFillIndicies() + (uint32)ellipse.GetNumberBorderIndicies();
	geomData.ExtendedIB = false;
	geomData.Topology = PrimitiveTopology::Triangles;

	return std::move( geomData );
}

// ================================ //
//
BufferRange			EllipseGeometry::BufferData							()
{
	// Rectangle doesn't use contants buffer.
	return BufferRange();
}

// ================================ //
//
filesystem::Path    EllipseGeometry::ShaderFunctionFile					()
{
	return "$(CoreGUI-Shader-Dir)/Geometry/ForwardAttributes.vsh";
}

// ================================ //
//
std::string		    EllipseGeometry::GeometryName						()
{
    return fmt::format( "EllipseGeometry-[Width={}][Height={}][StrokeThickness={}]", m_width, m_height, m_strokeThickness );
}

// ================================ //
//
AssetPath   		EllipseGeometry::ConstantsName						()
{
	// Rectangle doesn't use contants buffer.
	return AssetPath();
}

}	// gui
}	// sw
