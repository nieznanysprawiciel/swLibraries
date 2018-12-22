#pragma once
/**
@file Drawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "IDrawing.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"

#include "swCommonLib/Common/Buffers/BufferRange.h"


namespace sw {
namespace gui
{

class Brush;
class Geometry;


namespace impl
{


/**@brief Represents geometry using graphic API structures.

Vertex and Index Buffer contain both fill and border verticies/indicies.
Fill indicies start at offset 0 and end at offset FillEnd.
Border indicies directly follow fill indicies and end at BorderEnd.
Note that verticies layout in Vertex Buffer doesn't matter since indicies reference vertex buffer
from 0 position. That means that fill verticies can be used by border too.*/
struct GeometryRenderingData
{
	ResourcePtr< BufferObject >			VertexBuffer;		///< Vertex Buffer containing both fill and border verticies.
	ResourcePtr< BufferObject >			IndexBuffer;		///< Index Buffer containing both fill and border indicies.
	ResourcePtr< BufferObject >			GeometryConstants;	///< Constant buffer bound to Vertex Shader.
	ResourcePtr< VertexShader >			VertexShader;		///< Vertex Shader.
	ResourcePtr< ShaderInputLayout >	Layout;				///< Bertex layout.
	uint32								FillEnd;			///< End of fill indicies in buffer.
	uint32								BorderEnd;			///< End of border indicies in buffer.
	PrimitiveTopology					Topology;			///< Geometry topology.
	bool								ExtendedIB;			///< Index Buffer uses 4-bytes indicies.
};


/**@brief Represents brush using graphic API structures.*/
struct BrushRenderingData
{
	ResourcePtr< PixelShader >		PixelShader;		///< Pixel Shader.
	ResourcePtr< BufferObject >		BrushConstants;		///< Constant buffer bound to Pixel Shader.
	ResourcePtr< TextureObject >	Texture;			///< Optional texture bound to Pixel Shader.
};


}	// impl



/**@brief Simple rendering logic functionalities.

Advanced functionalities will be supported by DrawingGroup.

@ingroup Drawing*/
class Drawing : public IDrawing
{
	RTTR_ENABLE( IDrawing );
	RTTR_REGISTRATION_FRIEND

	FRIEND_CLASS_TESTER( Drawing )
private:

	impl::GeometryRenderingData		m_geometryData;
	impl::BrushRenderingData		m_brushData;
	impl::BrushRenderingData		m_penData;

protected:

	///@name Update rendering data.
	/// Derived classes should use these API functions to set rendering state.
	/// They shouldn't have direct access to rendering structures.
	///@{
	bool					UpdateBrushShader		( ShaderProvider* sp, Brush* brush );
	bool					UpdateBrushTexture		( ResourceManager* rm, Brush* brush );
	bool					UpdateBrushConstants	( ResourceManager* rm, Brush* brush );

	bool					UpdatePenShader			( ShaderProvider* sp, Brush* pen );
	bool					UpdatePenTexture		( ResourceManager* rm, Brush* pen );
	bool					UpdatePenConstants		( ResourceManager* rm, Brush* pen );

	bool					UpdateVertexShader		( ShaderProvider* sp, Geometry* geometry );
	bool					UpdateGeometry			( ResourceManager* rm, Geometry* geometry );
	bool					UpdateGeometryConstants	( ResourceManager* rm, Geometry* geometry );

	bool					CreateAndSetLayout		( ResourceManager* rm, ShaderProvider* sp, Geometry* geometry );
	///@}

	///@name Rendering functions.
	///@{

	/**@brief Updates Brush costants buffer content. Should be called before rendering.*/
	void					UpdateBrushCBContent	( IRenderer* renderer, Brush* brush );

	/**@brief Updates Pen costants buffer content. Should be called before rendering.*/
	void					UpdatePenCBContent		( IRenderer* renderer, Brush* pen );

	/**@brief Updates Geometry costants buffer content. Should be called before rendering.
	This function will update buffer conditionally, if it's necessary. 
	*/
	void					UpdateGeometryCBContent	( IRenderer* renderer, Geometry* pen );

	void					RenderFill				( IRenderer* renderer );
	void					RenderBorder			( IRenderer* renderer );

	///@}

private:

	bool					UpdateShaderImpl		( ShaderProvider* sp, Brush* brush, impl::BrushRenderingData& brushData );
	bool					UpdateTextureImpl		( ResourceManager* rm, Brush* brush, impl::BrushRenderingData& brushData );

	void					UpdateCBContentImpl		( IRenderer* renderer, Brush* brush, impl::BrushRenderingData& brushData );
	void					UpdateCBContentImpl		( IRenderer* renderer, BufferObject* buffer, BufferRange bufferData );

	void					RenderImpl				( IRenderer* renderer, impl::GeometryRenderingData& geom, impl::BrushRenderingData& brush, uint32 start, uint32 end );

public:

	explicit				Drawing	();
	virtual					~Drawing() = default;
};

DEFINE_PTR_TYPE( Drawing )


}	// gui
}	// sw

