#pragma once
/**
@file Generator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGeometrics/GeometricsCore/Types/IndexedGeometry.h"

#include "swGeometrics/GeometricsCore/Generators/Validation.h"



namespace sw {
namespace geom
{


namespace impl
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
template< typename VertexType, typename Generator >
void				GenerateSingleVertex		( VertexType& vertex, Size vertexIdx, Generator gen );

// ================================ //
//
template< typename VertexType, typename Generator, typename... Processors >
void				GenerateSingleVertex		( VertexType& vertex, Size vertexIdx, Generator gen, Processors...processors );

}	// impl

// ================================ //
//
template< typename Generator, typename... Processors >
Nullable< IndexedGeometry< typename Generator::VertexFormat, typename Generator::IndexFormat > >
					Generate					( Generator gen, Processors...processors );





//====================================================================================//
//			Implementation
//====================================================================================//

namespace impl
{

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
	ProcessSingleVertex( vertex, vertexIdx, processors... );
}

// ================================ //
//
template< typename VertexType, typename Generator >
void				GenerateSingleVertex		( VertexType& vertex, Size vertexIdx, Generator gen )
{
	gen.GenerateVertex( vertex, vertexIdx );
}

// ================================ //
//
template< typename VertexType, typename Generator, typename... Processors >
void				GenerateSingleVertex		( VertexType& vertex, Size vertexIdx, Generator gen, Processors... processors )
{
	gen.GenerateVertex( vertex, vertexIdx );
	ProcessSingleVertex( vertex, vertexIdx, processors... );
}


}	// impl


//====================================================================================//
//				Public API functions implementation
//====================================================================================//

// ================================ //
//
template< typename Generator, typename... Processors >
Nullable< IndexedGeometry< typename Generator::VertexFormat, typename Generator::IndexFormat > >
					Generate					( Generator gen, Processors... processors )
{
	ReturnResult result = Validate< typename Generator::VertexFormat, typename Generator::IndexFormat >( gen, processors... );

	if( result.IsValid() )
	{

		Size numVerticies = gen.GetNumberVerticies();
		Size numIndicies = gen.GetNumberIndicies();

		IndexedGeometry< typename Generator::VertexFormat, typename Generator::IndexFormat > geometry;
		geometry.Verticies.resize( numVerticies );
		geometry.Indicies.resize( numIndicies );

		for( Size idx = 0; idx < numVerticies; ++idx )
		{
			impl::GenerateSingleVertex( geometry.Verticies[ idx ], idx, gen, processors... );
		}

		gen.GenerateIndexBuffer( geometry.Indicies, 0 );

		return geometry;
	}
	else
		return result.GetError();
}

}	// geom
}	// sw
