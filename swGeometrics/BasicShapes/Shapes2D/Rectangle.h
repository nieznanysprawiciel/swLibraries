#pragma once
/**
@file Rectangle.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swGeometrics/GeometricsCore/Types/Accessors/DefaultAccessors.h"
#include "swGeometrics/GeometricsCore/Types/Traits/GeneratorTraits.h"


namespace sw {
namespace geom
{


/**@brief Rectangle generator.
@ingroup Shapes2D*/
template< typename VertexType, typename IndexType, typename PositionAcc = DefaultPositionAcc< VertexType > >
class Rectangle : public GeneratorTraits< VertexType, IndexType >
{
private:
public:

	float				TopLeftX;
	float				TopLeftY;
	float				Width;
	float				Height;

public:

	inline explicit		Rectangle				();


	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );
	
	template< class IndexBuffer >
	inline void			GenerateIndexBuffer		( IndexBuffer& idxBuffer, Size startIdx );

	inline Size			GetNumberVerticies		() const;
	inline Size			GetNumberIndicies		() const;

	inline ReturnResult	ValidateParams			() const;

};




}	// geom
}	// sw


#include "Rectangle.inl"

