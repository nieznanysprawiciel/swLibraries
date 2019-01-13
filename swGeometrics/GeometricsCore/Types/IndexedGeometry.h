#pragma once
/**
@file IndexGeometry.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include <vector>

namespace sw {
namespace geom
{


/**@brief Structure storing indexed geometry.*/
template< typename VertexType, typename IndexType >
struct IndexedGeometry
{
	typedef std::vector< VertexType >	VertexVec;
	typedef std::vector< IndexType >	IndexVec;

	VertexVec	Verticies;
	IndexVec	Indicies;


	// ================================ //
	//
	explicit IndexedGeometry	( Size numVerticies, Size numIndicies )
		: Verticies( numVerticies )
		, Indicies( numIndicies )
	{}
};



}	// geom
}	// sw

