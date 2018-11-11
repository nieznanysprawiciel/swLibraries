#pragma once
/**
@file Generator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swGeometrics/GeometricsCore/Types/IndexedGeometry.h"



namespace sw {
namespace geom
{

// ================================ //
//
template< typename VertexType, typename Processor >
void				ProcessSingleVertex			( VertexType& vertex, Size vertexIdx, Processor processor );

// ================================ //
//
template< typename VertexType, typename Processor, typename... Processors >
void				ProcessSingleVertex			( VertexType& vertex, Size vertexIdx, Processor processor, Processors... processors );

// ================================ //
//
template< typename VertexType, typename Generator, typename... Processors >
void				GenerateSingleVertex		( VertexType& vertex, Size vertexIdx, Generator gen, Processors...processors );


// ================================ //
//
template< typename Generator, typename... Processors >
void				Generate					( Generator gen, Processors...processors );





//====================================================================================//
//			Implementation
//====================================================================================//


// ================================ //
//
template< typename VertexType, typename Processor >
void				ProcessSingleVertex			( VertexType& vertex, Size vertexIdx, Processor processor )
{
	processor.GenerateVertex( vertex, vertexIdx );
}

// ================================ //
//
template< typename VertexType, typename Processor, typename... Processors >
void				ProcessSingleVertex			( VertexType& vertex, Size vertexIdx, Processor processor, Processors... processors )
{
	processor.GenerateVertex( vertex, vertexIdx );
	ProcessSingleVertex( vertex, vertexIdx, processors );
}

// ================================ //
//
template< typename VertexType, typename Generator, typename... Processors >
void				GenerateSingleVertex		( VertexType& vertex, Size vertexIdx, Generator gen, Processors... processors )
{
	gen.GenerateVertex( vertex, vertexIdx );
	ProcessSingleVertex( vertex, vertexIdx, processors );
}

// ================================ //
//
template< typename Generator, typename ...Processors >
void				Generate					( Generator gen, Processors... processors )
{
	Size numVerticies = gen.GetNumberVerticies();

	IndexedGeometry< typename Generator::VertexFormat, uint16 > geometry;
	geometry.Verticies.resize( numVerticies );
	//geometry.Indicies.resize( numIndicies );
	
	for( Size idx = 0; idx < numVerticies; ++idx )
	{
		GenerateSingleVertex( geometry.Verticies[ idx ], idx, gen, processors );
	}
}

}	// geom
}	// sw
