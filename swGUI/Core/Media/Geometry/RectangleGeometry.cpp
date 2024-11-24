/**
@file RectangleGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "RectangleGeometry.h"

#include "swGeometrics/BasicShapes/Shapes2D/RectangleWithBorder.h"
#include "swGeometrics/BasicShapes/CoordsUV/PlanarUV.h"
#include "swGeometrics/GeometricsCore/Generators/Generator.h"

#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"
#include "swCommonLib/Common/Buffers/IndexedGeometryBuffer.h"

#include "swCommonLib/Common/Converters.h"


namespace sw {
namespace gui
{

// ================================ //
//
RectangleGeometry::RectangleGeometry()
	:	Geometry( Geometry::ConstantBufferMode::Disable )
{}

// ================================ //
//
void				RectangleGeometry::SetWidth			( float width )
{
	m_width = width;
	InvalidateGeometry();
}

// ================================ //
//
void				RectangleGeometry::SetHeight		( float height )
{
	m_height = height;
	InvalidateGeometry();
}

// ================================ //
//
void				RectangleGeometry::SetThickness		( float thickness )
{
	m_strokeThickness = thickness;
	InvalidateGeometry();
}

// ================================ //
//
bool				RectangleGeometry::HitTest			( const Point& point ) const
{
    return Rect{ 0.0, m_width, 0.0, -m_height }.Intersects( point );
}

// ================================ //
//
bool				RectangleGeometry::HitTest			( const Rect& rectangle ) const
{
    return Rect{ 0.0, m_width, 0.0, -m_height }.Intersects( rectangle );
}

// ================================ //
//
Nullable< GeometryData >	RectangleGeometry::Generate()
{
	geom::RectangleWithBorder< VertexShape2D, Index16 > rect;
	rect.TopLeftX = 0.0f;
	rect.TopLeftY = 0.0f;
	rect.Width = m_width;
	rect.Height = m_height;
	rect.StrokeThickness = m_strokeThickness;

	geom::PlanarUV< VertexShape2D > planarUV;
	planarUV.MinX = 0.0f;
	planarUV.MinY = -m_height;
	planarUV.MaxX = m_width;
	planarUV.MaxY = 0.0f;

	auto geometry = geom::Generate< geom::IndexedGeometryBuffer< VertexShape2D, Index16 > >( rect, planarUV );
    ReturnIfInvalid( geometry );

	GeometryData geomData( geometry.Get().Verticies.MoveToRawBuffer(), geometry.Get().Indicies.MoveToRawBuffer() );
	geomData.FillIdxEnd = (uint32)rect.GetNumberFillIndicies();
	geomData.BorderIdxEnd = (uint32)rect.GetNumberFillIndicies() + (uint32)rect.GetNumberBorderIndicies();
	geomData.ExtendedIB = false;
	geomData.Topology = PrimitiveTopology::Triangles;

	return std::move( geomData );
}

// ================================ //
//
BufferRange					RectangleGeometry::BufferData		()
{
	// Rectangle doesn't use contants buffer.
	return BufferRange();
}

// ================================ //
//
fs::Path			RectangleGeometry::ShaderFunctionFile	()
{
	return "$(CoreGUI-Shader-Dir)/Geometry/ForwardAttributes.vsh";
}

// ================================ //
//
std::string		    RectangleGeometry::GeometryName		()
{
    return fmt::format( "RectangleGeometry-[Width={}][Height={}][StrokeThickness={}]", m_width, m_height, m_strokeThickness );
}

// ================================ //
//
AssetPath   		RectangleGeometry::ConstantsName	()
{
	// Rectangle doesn't use contants buffer.
	return AssetPath();
}

}	// gui
}	// sw
