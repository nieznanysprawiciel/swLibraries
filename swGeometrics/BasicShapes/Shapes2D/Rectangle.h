#pragma once
/**
@file Rectangle.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swGeometrics/GeometricsCore/Types/Accessors/Default.h"


namespace sw {
namespace geom
{


/**@brief Rectangle generator.
@ingroup Shapes2D*/
template< typename VertexType, typename IndexType, typename PositionAcc = DefaultPositionAcc< VertexType > >
class Rectangle
{
private:
public:

	float				TopLeftX;
	float				TopLeftY;
	float				Width;
	float				Height;
	float				Z;

public:

	inline explicit		Rectangle				();


	inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );
	//inline void			GenerateIndexBuffer		();

	inline Size			GetNumberVerticies		() const;

public:

	typedef VertexType VertexFormat;
	typedef IndexType IndexFormat;
};





}	// geom
}	// sw


#include "Rectangle.inl"

