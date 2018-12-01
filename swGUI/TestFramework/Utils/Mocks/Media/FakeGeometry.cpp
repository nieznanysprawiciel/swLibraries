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
FakeGeometry::FakeGeometry( bool sharedBuffer )
	:	Geometry( sharedBuffer )
	,	m_geomName( L"InitGeom" )
{}


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
BufferRange		FakeGeometry::BufferData	()
{
	return BufferRange();
}

// ================================ //
//
std::string		FakeGeometry::ShaderFunctionFile	()
{
	return m_shaderFun;
}

// ================================ //
//
std::wstring	FakeGeometry::GeometryName			()
{
	return m_geomName;
}

// ================================ //
//
std::wstring	FakeGeometry::ConstantsName			()
{
	return std::wstring();
}

// ================================ //
//
void			FakeGeometry::ChangeGeometry		( const std::wstring& geomName )
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

}	// gui
}	// sw
