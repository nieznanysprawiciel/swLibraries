#pragma once
/**
@file Geometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"

#include "swGUI/Core/System/CommonTypes/CommonTypes.h"


/**@defgroup Geometries Geometries
@brief Geometric shapes.
@ingroup Media*/


namespace sw {
namespace gui
{


/**@brief Class representing geometry.

Classes derived from Geometry can generate geometrical shapes, check mouse intersections
and provide VertexShader information for @ref RenderingSystem. Derive your own classes from this object
to add new geometrical shapes to gui framework.

@ingroup Geometries*/
class Geometry : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND

	friend class RenderingSystem;
private:

	bool			m_invalidateGeometry : 1;
	bool			m_invalidateConstants : 1;
	bool			m_invalidateShader : 1;

protected:

	///@name Derived classes API
	///@{

	void			InvalidateGeometry		();
	void			InvalidateConstants		();
	void			InvalidateShader		();

	///@}

public:

	///@name Hit testing
	///@{

	/**@brief Check intersection of geometry shape with point.*/
	virtual bool	HitTest					( const Point& point )			= 0;

	/**@brief Check intersection of geometry shape with rectangle.*/
	virtual bool	HitTest					( const Rect& rectangle )		= 0;

	///@}

public:

	///@name Shapes generation API
	///@{
	//virtual	Verticies	Generate			() = 0;
	//virtual	BufferPtr	BufferData			() = 0;

	/**@brief Returns file name containing function used in Vertex Shader.
	
	Vertex Shader is combined from shader template and function defined by Geometry.
	Shader template is defined by swGUI framework and it applies standard transformations to verticies.
	
	Geometry can be generated only on CPU or it can be generated on CPU and then modified in shader depending
	on parameters in Constant Buffer. After calling Geometry defined function, standard framework transformations
	are applied.

	This way geometry can be generated once for multiple parameters of shape to avoid data transfers between
	CPU and GPU. You should override @ref Geometry::GeometryName function, to return the same name, if Vertex
	Buffer shouldn't be updated.*/
	virtual std::string		ShaderFunctionFile	() = 0;

	/**@brief Returns key used to store/find geometry buffers (VB and IB) in resources.
	
	This function should return name of buffer based on shape parameters. You can use the same
	geometry for different parameters and modify it in Vertex Shader. If you want to use the same
	buffer for different parameters ranges, return the same name from this function for these ranges.*/
	virtual std::string		GeometryName		() = 0;

	///@}

};



}	// gui
}	// sw





