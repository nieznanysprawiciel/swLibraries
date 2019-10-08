/**
@file FakeGeometry.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/TestFramework/stdafx.h"


#include "FakeGeometry.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"



namespace sw {
namespace gui
{

// ================================ //
//
FakeGeometry::FakeGeometry( Geometry::ConstantBufferMode cbMode )
	:	Geometry( cbMode )
	,	m_geomName( "InitGeom" )
{
	InvalidateShader();
	InvalidateConstants();
	InvalidateGeometry();
}


// ================================ //
//
bool			FakeGeometry::HitTest		( const Point& point )
{
	assert( !"Implement me" );
	return false;
}

// ================================ //
//
bool			FakeGeometry::HitTest		( const Rect& rectangle )
{
	assert( !"Implement me" );
	return false;
}

// ================================ //
//
GeometryData	FakeGeometry::Generate		()
{
	BufferTyped< VertexShape2D > vertexBuffer( 4 );
	BufferTyped< Index16 > indexBuffer( 6 );

	GeometryData data( vertexBuffer.MoveToRawBuffer(), indexBuffer.MoveToRawBuffer() );

	return data;
}

// ================================ //
//
BufferRange		        FakeGeometry::BufferData	()
{
	return m_buffer.GetView();
}

// ================================ //
//
filesystem::Path		FakeGeometry::ShaderFunctionFile	()
{
	return m_shaderFun;
}

// ================================ //
//
std::string	            FakeGeometry::GeometryName			()
{
	return m_geomName;
}

// ================================ //
//
AssetPath	        FakeGeometry::ConstantsName			()
{
	return AssetPath( "", "FakeGeometry" );
}

// ================================ //
//
void			FakeGeometry::ChangeGeometry		( const std::string& geomName )
{
	m_geomName = geomName;
	InvalidateGeometry();
}

// ================================ //
//
void			FakeGeometry::SetShaderFunction		( const std::string& shaderFun )
{
	m_shaderFun = shaderFun;
	InvalidateShader();
}

// ================================ //
//
void			FakeGeometry::SetHeight				( float height )
{
	m_buffer.Height = height;
	InvalidateConstants();
}

// ================================ //
//
void			FakeGeometry::SetWidth				( float width )
{
	m_buffer.Width = width;
	InvalidateConstants();
}

}	// gui
}	// sw
