/**
@file TextGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "TextGeometry.h"

#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"

#include "swCommonLib/Common/Buffers/IndexedGeometryBuffer.h"
#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/Common/fmt.h"

#include "swGeometrics/BasicShapes/CoordsUV/PlanarUV.h"
#include "swGeometrics/GeometricsCore/Generators/Generator.h"




namespace sw {
namespace gui
{

// ================================ //
//
TextGeometry::TextGeometry( FontAssetPtr font )
	: Geometry( Geometry::ConstantBufferMode::Disable ) 
    , m_font( font ) {}

// ================================ //

void                TextGeometry::SetText( const std::wstring& text )
{
    m_text = text;
    InvalidateGeometry();
}

// ================================ //

void				TextGeometry::SetFont( FontAssetPtr font )
{
    m_font = font;
    InvalidateGeometry();
}

// ================================ //
//
void				TextGeometry::SetWidth( float width )
{
    m_width = width;
    InvalidateGeometry();
}

// ================================ //
//
void				TextGeometry::SetHeight( float height )
{
    m_height = height;
    InvalidateGeometry();
}


// ================================ //
//
bool                TextGeometry::HitTest( const Point& point ) const
{
    return Rect{ 0.0, m_width, 0.0, m_height }.Intersects( point );
}

// ================================ //
//
bool                TextGeometry::HitTest( const Rect& rectangle ) const
{
    return Rect{ 0.0, m_width, 0.0, m_height }.Intersects( rectangle );
}

// ================================ //
//
GeometryData		TextGeometry::Generate			()
{
    auto arranger = TextArranger::CreateFrom( m_font );
    arranger.Bounds = Rect{ 0.0, m_width, 0.0, m_height };
    arranger.WrapText = true;
    arranger.TextAlign = TextAlignment::Left;
    
    auto geometry = arranger.GenerateGeometryTextured( m_text, m_font, true );
    auto numIndicies = geometry.Get().Indicies.ElementsCount();

	GeometryData geomData( geometry.Get().Verticies.MoveToRawBuffer(), geometry.Get().Indicies.MoveToRawBuffer() );
    // The roles are reversed. Fill is background and border is text.
	geomData.FillIdxEnd = (uint32)arranger.NumBorderIndicies();
    geomData.BorderIdxEnd = (uint32)numIndicies;
	geomData.ExtendedIB = true;
	geomData.Topology = PrimitiveTopology::Triangles;

	return geomData;
}

// ================================ //
//
BufferRange			TextGeometry::BufferData		()
{
	// Rectangle doesn't use contants buffer.
	return BufferRange();
}

// ================================ //
//
filesystem::Path    TextGeometry::ShaderFunctionFile	()
{
	return "$(CoreGUI-Shader-Dir)/Geometry/ForwardWithOpacity.vsh";
}

// ================================ //
//
std::string		    TextGeometry::GeometryName		()
{
    return fmt::format( "/TextGeometry{}", m_font->GetAssetPath().GetInternalPath() );
}

// ================================ //
//
AssetPath   		TextGeometry::ConstantsName	()
{
	// Rectangle doesn't use contants buffer.
	return AssetPath();
}

}	// gui
}	// sw
