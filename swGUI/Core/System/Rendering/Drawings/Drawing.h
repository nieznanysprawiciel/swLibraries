#pragma once
/**
@file Drawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "IDrawing.h"

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw {
namespace gui
{

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
	ResourcePtr< BufferObject >		VertexBuffer;		///< Vertex Buffer containing both fill and border verticies.
	ResourcePtr< BufferObject >		IndexBuffer;		///< Index Buffer containing both fill and border indicies.
	ResourcePtr< BufferObject >		GeometryConstants;	///< Constant buffer bound to Vertex Shader.
	ResourcePtr< VertexShader >		VertexShader;		///< Vertex Shader.
	uint32							FillEnd;			///< End of fill indicies in buffer.
	uint32							BorderEnd;			///< End of border indicies in buffer.
	PrimitiveTopology				Topology;			///< Geometry topology.
	bool							ExtendedIB;			///< Index Buffer uses 4-bytes indicies.
};


/**@brief Represents brush using graphic API structures.*/
struct BrushRenderingData
{
	ResourcePtr< PixelShader >		PixelShader;		///< Vertex Shader.
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
private:

	impl::GeometryRenderingData		m_geometryData;
	impl::BrushRenderingData		m_brushData;
	impl::BrushRenderingData		m_penData;

public:


};


}	// gui
}	// sw

