#pragma once
/**
@file RectangleWithBorder.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGeometrics/BasicShapes/Shapes2D/Rectangle.h"


namespace sw {
namespace geom
{

/**@brief Rectangle with border for GUI.
@ingroup Shapes2D*/
template< typename VertexType, typename IndexType, typename PositionAcc = DefaultPositionAcc< VertexType > >
class RectangleWithBorder : public Rectangle< VertexType, PositionAcc >
{
private:

	typedef Rectangle< VertexType, IndexType, PositionAcc > Parent;

public:

	float				StrokeThickness;

public:

	inline explicit		RectangleWithBorder		();


	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );
	
	template< class IndexBuffer >
	inline void			GenerateIndexBuffer		( IndexBuffer& idxBuffer, Size startIdx );

	inline Size			GetNumberVerticies		() const;
	inline Size			GetNumberIndicies		() const;

	ReturnResult		ValidateParams			() const;

};




}	// geom
}	// sw

