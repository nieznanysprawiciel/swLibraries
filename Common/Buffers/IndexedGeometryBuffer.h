#pragma once
/**
@file IndexedGeometryBuffer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Buffers/BufferTyped.h"


namespace sw {
namespace geom
{


/**@brief Structure for storing indexed geometry in memory buffer.
Structure uses BufferTyped to store both index and vertex buffers.

@todo In future buffers should support custom allocators.
@todo Move to swGeometrics. Create new library for objects dependent on RTTR.*/
template< typename VertexType, typename IndexType >
struct IndexedGeometryBuffer
{
	BufferTyped< VertexType >		Verticies;
	BufferTyped< IndexType >		Indicies;



	// ================================ //
	//
	explicit IndexedGeometryBuffer	( Size numVerticies, Size numIndicies )
		: Verticies( numVerticies )
		, Indicies( numIndicies )
	{}

	// ================================ //
	//
	IndexedGeometryBuffer( IndexedGeometryBuffer&& geom )
		: Verticies( std::move( geom.Verticies ) )
		, Indicies( std::move( geom.Indicies ) )
	{}
};



}	// geom
}	// sw


