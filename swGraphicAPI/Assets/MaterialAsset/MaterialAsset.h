#pragma once
/**
@file MaterialAsset.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/Resources/Textures/Texture.h"
#include "swGraphicAPI/Resources/Buffers/Buffer.h"

#include "ShadingModelData.h"
#include "MaterialAssetInitData.h"
#include "MaterialInfo.h"

#include <vector>


namespace sw
{


/**@defgroup Assets Assets

@brief High level engine resources.
*/


/**@defgroup Materials Materials

@brief Classes describing materials.

Class @ref MaterialAsset is main material class used by engine.

@ingroup Assets
*/




/**@brief Class describes Material.

Material consists of shaders that will be used to render scene element.
Only VertexShader and PixelShader fileds are necessary. GeometryShader will be used
only if it is set. Tesselation will be tuned on if both ControlsShader and EvaluationShader
will be present.

Material has it's own buffer with shading parameters. It will be initialized with ShadingData
from MaterialInfo structure. There's only single Buffer per material instance. We can parametrize
Material by binding to shaders additional buffers with different parameters per scene entity.
To do this we should fill @ref MaterialInfo::ParametricBuffers field.

@ingroup Assets
@ingroup Materials
*/
class MaterialAsset : public Resource
{
	RTTR_ENABLE( Resource );
    RTTR_REGISTRATION_FRIEND;
private:

	BufferPtr		                m_materialBuffer;						///< GPU buffer containing material data.
	VertexShaderPtr		            m_vertexShader;							///< Vertex shader.
	PixelShaderPtr		            m_pixelShader;							///< Pixel shader.
	TexturePtr	                    m_textures[ MAX_MATERIAL_TEXTURES ];	///< Textures set.

	GeometryShaderPtr	            m_geometryShader;		///< [Optional] Geometry shader.
	ControlShaderPtr	            m_controlShader;		///< [Optional] Shader invoked before tesselation.
	EvaluationShaderPtr	            m_evaluationShader;		///< [Optional] Shader invoked after tesselation.


	MaterialInfo					m_descriptor;			///< Material descriptor.

public:
	explicit			MaterialAsset		( AssetPath filePath, MaterialInitData&& initData );

public:

	const BufferPtr&		                GetMaterialBuffer		() const { return m_materialBuffer; }
	const VertexShaderPtr&		            GetVertexShader			() const { return m_vertexShader; }
	const PixelShaderPtr&		            GetPixelShader			() const { return m_pixelShader; }
	const GeometryShaderPtr&	            GetGeometryShader		() const { return m_geometryShader; }
	const ControlShaderPtr&		            GetTessControlShader	() const { return m_controlShader; }
	const EvaluationShaderPtr&	            GetTessEvaluationShader	() const { return m_evaluationShader; }

	const TexturePtr&		                GetTexture		( int index ) const { return m_textures[ index ]; }
	const MaterialInfo&						GetDescriptor	() const { return m_descriptor; }

private:
	~MaterialAsset();

	// Temporary textures getters for properties.
	Texture*		GetTexture1() const { return m_textures[ 0 ].Ptr(); }
	Texture*		GetTexture2() const { return m_textures[ 1 ].Ptr(); }
	Texture*		GetTexture3() const { return m_textures[ 2 ].Ptr(); }
	Texture*		GetTexture4() const { return m_textures[ 3 ].Ptr(); }
	Texture*		GetTexture5() const { return m_textures[ 4 ].Ptr(); }
	Texture*		GetTexture6() const { return m_textures[ 5 ].Ptr(); }
	Texture*		GetTexture7() const { return m_textures[ 6 ].Ptr(); }
	Texture*		GetTexture8() const { return m_textures[ 7 ].Ptr(); }
};

}	// sw
