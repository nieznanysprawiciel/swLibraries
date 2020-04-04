#pragma once
/**
@file EllipseWithBorder.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Ellipse.h"


namespace sw {
namespace geom
{




/**@brief Ellipse with border generator for GUI.
@ingroup Shapes2D*/
template< typename VertexType, typename IndexType, typename PositionAcc = DefaultPositionAcc< VertexType > >
class EllipseWithBorder : public Ellipse< VertexType, IndexType, PositionAcc >
{
private:

	typedef Ellipse< VertexType, IndexType, PositionAcc > Parent;

public:

	float				StrokeThickness;

public:

	inline explicit		EllipseWithBorder		();


	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );
	
	template< class IndexBuffer >
	inline void			GenerateIndexBuffer		( IndexBuffer& idxBuffer, Size startIdx );

	inline Size			GetNumberVerticies		() const;
	inline Size			GetNumberIndicies		() const;

	inline Size			GetNumberFillIndicies	() const;
	inline Size			GetNumberBorderIndicies	() const;

	inline ReturnResult	ValidateParams			() const;

};


}	// geom
}	// sw

#include "EllipseWithBorder.inl"
