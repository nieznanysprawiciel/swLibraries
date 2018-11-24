#pragma once
/**
@file Circle.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"
#include "swGeometrics/GeometricsCore/Types/Accessors/DefaultAccessors.h"
#include "swGeometrics/GeometricsCore/Types/Traits/GeneratorTraits.h"


namespace sw {
namespace geom
{


/**@brief Circle generator.
@ingroup Shapes2D*/
template< typename VertexType, typename IndexType, typename PositionAcc = DefaultPositionAcc< VertexType > >
class Circle : public GeneratorTraits< VertexType, IndexType >
{
private:
public:

	float				Radius;
	uint32				Tesselation;

public:

	inline explicit		Circle					();


	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );
	
	template< class IndexBuffer >
	inline void			GenerateIndexBuffer		( IndexBuffer& idxBuffer, Size startIdx );

	inline Size			GetNumberVerticies		() const;
	inline Size			GetNumberIndicies		() const;

	ReturnResult		ValidateParams			() const;

private:

	template< class IndexBuffer >
	inline void			AddTriangle				( IndexBuffer& idxBuffer, IndexType startIdx, IndexType vertIdx1, IndexType vertIdx2, IndexType vertIdx3 );
};





}	// geom
}	// sw


#include "Circle.inl"
