#pragma once
/**
@file Ellipse.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/Common/TypesDefinitions.h"
#include "swGeometrics/GeometricsCore/Types/Accessors/DefaultAccessors.h"
#include "swGeometrics/GeometricsCore/Types/Traits/GeneratorTraits.h"




namespace sw {
namespace geom
{



/**@brief Ellipse generator.
@ingroup Shapes2D*/
template< typename VertexType, typename IndexType, typename PositionAcc = DefaultPositionAcc< VertexType > >
class Ellipse : public GeneratorTraits< VertexType, IndexType >
{
private:
public:

	float				Width;
	float				Height;
	uint32				Tesselation;

public:

	inline explicit		Ellipse					();


	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );
	
	template< class IndexBuffer >
	inline void			GenerateIndexBuffer		( IndexBuffer& idxBuffer, Size startIdx );

	inline Size			GetNumberVerticies		() const;
	inline Size			GetNumberIndicies		() const;

	inline ReturnResult	ValidateParams			() const;

};



}	// geom
}	// sw

#include "Ellipse.inl"
