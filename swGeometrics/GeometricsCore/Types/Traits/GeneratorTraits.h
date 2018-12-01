#pragma once
/**
@file Traits.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"

#include <type_traits>


namespace sw {
namespace geom
{


namespace impl
{

// ================================ //
//
class EnableIsGenerator
{};

}	// impl


// ================================ //
//
template< typename VertexType, typename IndexType >
class GeneratorTraits : public impl::EnableIsGenerator
{
private:
public:

	typedef VertexType VertexFormat;
	typedef IndexType IndexFormat;

protected:

	///@name Helpers for Generators
	///@{

	/**@brief Adds triangle to provided index buffer.
	Function moves startIdx to new position after added trangle.
	Note that in both functions @ref AddTriangleCW and @ref AddTriangleCCW expect, that provided 
	vertIdx1, vertIdx2 and vertIdx3 will be in clockwise order.
	
	@todo In future we should to template function with WindingOrder parameter.*/
	template< class IndexBuffer >
	inline void			AddTriangleCW		( IndexBuffer& idxBuffer, Size& startIdx, IndexType vertIdx1, IndexType vertIdx2, IndexType vertIdx3 );

	/**@brief Adds triangle to provided index buffer.
	Check @ref AddTriangleCW.*/
	template< class IndexBuffer >
	inline void			AddTriangleCCW		( IndexBuffer& idxBuffer, Size& startIdx, IndexType vertIdx1, IndexType vertIdx2, IndexType vertIdx3 );


	///@}

};


// ================================ //
//
template< typename Type >
struct isGenerator
{	
	static const bool value = std::is_base_of< impl::EnableIsGenerator, Type >::value;
};


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename VertexType, typename IndexType >
template< typename IndexBuffer >
inline void			GeneratorTraits< VertexType, IndexType >::AddTriangleCW
																(	IndexBuffer& idxBuffer,
																	Size& startIdx,
																	IndexType vertIdx1,
																	IndexType vertIdx2,
																	IndexType vertIdx3 )
{
	idxBuffer[ startIdx ] = vertIdx1;
	idxBuffer[ startIdx + 1 ] = vertIdx2;
	idxBuffer[ startIdx + 2 ] = vertIdx3;

	startIdx += 3;
}

// ================================ //
//
template< typename VertexType, typename IndexType >
template< typename IndexBuffer >
inline void			GeneratorTraits< VertexType, IndexType >::AddTriangleCCW
																(	IndexBuffer& idxBuffer,
																	Size& startIdx,
																	IndexType vertIdx1,
																	IndexType vertIdx2,
																	IndexType vertIdx3 )
{
	idxBuffer[ startIdx ] = vertIdx1;
	idxBuffer[ startIdx + 1 ] = vertIdx3;
	idxBuffer[ startIdx + 2 ] = vertIdx2;

	startIdx += 3;
}


}	// geom
}	// sw


