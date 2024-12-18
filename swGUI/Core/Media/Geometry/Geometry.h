#pragma once
/**
@file Geometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Object.h"
#include "swCommonLib/Common/Buffers/BufferRaw.h"
#include "swCommonLib/Common/Buffers/BufferRange.h"

#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"

#include "swGUI/Core/System/CommonTypes/CommonTypes.h"
#include "swGUI/Core/System/CommonTypes/UpdateTracker.h"


/**@defgroup Geometries Geometries
@brief Geometric shapes.
@ingroup Media*/


namespace sw {
namespace gui
{


/**@brief Structure holding generated geometry.
@ingroup Geometries*/
struct GeometryData
{
	BufferRaw			VertexBuffer;
	BufferRaw			IndexBuffer;
	uint32				FillIdxEnd;
	uint32				BorderIdxEnd;
	PrimitiveTopology	Topology;
	bool				ExtendedIB;			///< Index Buffer uses 4-bytes indicies.

	// ================================ //
	//
	GeometryData( BufferRaw&& vertexBuffer, BufferRaw&& indexBuffer )
		: VertexBuffer( std::move( vertexBuffer ) )
		, IndexBuffer( std::move( indexBuffer ) )
		, FillIdxEnd( 0 )
		, BorderIdxEnd( 0 )
		, Topology( PrimitiveTopology::Triangles )
		, ExtendedIB( false )
	{}
};


/**@brief Class representing geometry.

Classes derived from Geometry can generate geometrical shapes, check mouse intersections
and provide VertexShader information for @ref RenderingSystem. Derive your own classes from this object
to add new geometrical shapes to gui framework.

Check in @ref Drawing class, what should be preferred vertex layout. If you need other layout, you should
subclass Drawing class.

@ingroup Geometries*/
class Geometry : public Object
{
	RTTR_ENABLE( Object );
	RTTR_REGISTRATION_FRIEND

	friend class RenderingSystem;
	friend class Drawing;

public:

	enum class ConstantBufferMode: u8
	{
		Disable,		///< Buffer will not be used.
		UseShared,		///< Multiple Geometries will use single buffer. Update will happen every render.
		UsePrivate		///< This instance will have it's own buffer. Buffer will be updated on demand.
	};

private:

	UpdateCounter16		m_shaderState;
    UpdateCounter16		m_geometryState;
    UpdateCounter16		m_constantsState;

	bool			m_useConstantBuffer : 1;
	bool			m_sharedBuffer : 1;

public:

	explicit		Geometry	( ConstantBufferMode cbMode );

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
	virtual bool	HitTest					( const Point& point ) const		= 0;

	/**@brief Check intersection of geometry shape with rectangle.*/
	virtual bool	HitTest					( const Rect& rectangle ) const		= 0;

	///@}

public:

	///@name Shapes generation API
	///@{

	/**@brief Generates geometry with current parameters.*/
	virtual	Nullable< GeometryData >	    Generate			() = 0;
	
	/**@brief Returns BufferRange of new content of constant buffer.
	@note Geometry object is still owner of returned memory and it shouldn't be freed after return from this function.
	It is recommended to use @ref StackBuffer in Geometry implementation.*/
	virtual	BufferRange						BufferData			() = 0;

	/**@brief Returns file name containing function used in Vertex Shader.
	
	Vertex Shader is combined from shader template and function defined by Geometry.
	Shader template is defined by swGUI framework and it applies standard transformations to verticies.
	
	Geometry can be generated only on CPU or it can be generated on CPU and then modified in shader depending
	on parameters in Constant Buffer. After calling Geometry defined function, standard framework transformations
	are applied.

	This way geometry can be generated once for multiple parameters of shape to avoid data transfers between
	CPU and GPU. You should override @ref Geometry::GeometryName function, to return the same name, if Vertex
	Buffer shouldn't be updated.*/
	virtual fs::Path						ShaderFunctionFile	() = 0;

	/**@brief Returns key used to store/find geometry buffers (VB and IB) in resources.
	
	This function should return name of buffer based on shape parameters. You can use the same
	geometry for different parameters and modify it in Vertex Shader. If you want to use the same
	buffer for different parameters ranges, return the same name from this function for these ranges.*/
	virtual std::string   					GeometryName		() = 0;


	/**@brief Returns key used to store/find contant buffer in resources.*/
	virtual AssetPath   					ConstantsName		() = 0;
	///@}


protected:

	///@name RenderingSystem API
	///@{

	void            ShaderUpdated		( UpdateTracker16& tracker );
    void            GeometryUpdated		( UpdateTracker16& tracker );
    void            ConstantsUpdated	( UpdateTracker16& tracker );

	const UpdateCounter16&		ShaderState		() const { return m_shaderState; }
    const UpdateCounter16&		GeometryState	() const { return m_geometryState; }
    const UpdateCounter16&		ConstantsState	() const { return m_constantsState; }

	bool			NeedsShaderUpdate		( const UpdateTracker16& tracker ) const { return m_shaderState.NeedsUpdate( tracker ); }
	bool			NeedsGeometryUpdate		( const UpdateTracker16& tracker ) const { return m_geometryState.NeedsUpdate( tracker ); }
	bool			NeedsConstantsUpdate	( const UpdateTracker16& tracker ) const { return m_constantsState.NeedsUpdate( tracker ); }
	
	bool			UsesSharedBuffer	() const { return m_sharedBuffer; }
	bool			UsesConstantBuffer	() const { return m_useConstantBuffer; }

	///@}
};

DEFINE_PTR_TYPE( Geometry )


}	// gui
}	// sw





