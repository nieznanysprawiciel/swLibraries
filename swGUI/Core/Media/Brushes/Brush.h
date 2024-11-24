#pragma once
/**
@file Brush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Object.h"
#include "swCommonLib/Common/Buffers/BufferRange.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"
#include "swGUI/Core/System/CommonTypes/UpdateTracker.h"


/**@defgroup Brushes Brushes
@brief Brushes.
@ingroup Media*/



namespace sw {
namespace gui
{

/**@brief Brush base class.

@ingroup Brushes*/
class Brush : public Object
{
	RTTR_ENABLE( Object );
	RTTR_REGISTRATION_FRIEND;

	friend class Drawing;
	friend class RenderingSystem;

public:

	enum class ConstantBufferMode
	{
		Enable,
		Disable
	};

private:

	bool			m_useConstantBuffer : 1;

	UpdateCounter16		m_shaderState;
    UpdateCounter16		m_textureState;
    UpdateCounter16		m_constantsState;

protected:

	///@name Derived classes API
	///@{

	void			InvalidateConstants		();
	void			InvalidateShader		();
	void			InvalidateTexture		();

	///@}

public:

	explicit		Brush		( ConstantBufferMode enableCB );
	virtual			~Brush		() = default;

	/**@brief Returns BufferRange of new content of constant buffer.
	@note Brush object is still owner of returned memory and it shouldn't be freed after return from this function.
	It is recommended to use @ref StackBuffer in Brush implementation.*/
	virtual	BufferRange		    BufferData			() = 0;

	/**@brief Returns file name containing function used in Pixel Shader.
	
	Pixel Shader is combined from shader template and function defined by the Brush.*/
	virtual fs::Path			ShaderFunctionFile	() = 0;

	/**@brief Name of texture to find in @ref ResourceManager.*/
	virtual AssetPath	        TextureSource		() = 0;

	/**@brief Returns key used to store/find contant buffer in resources.*/
	virtual AssetPath	        ConstantsName		() = 0;

private:

	///@name RenderingSystem API
	///@{

	void            ShaderUpdated( UpdateTracker16& tracker );
    void            TextureUpdated( UpdateTracker16& tracker );
    void            ConstantsUpdated( UpdateTracker16& tracker );

protected:

	const UpdateCounter16&		ShaderState		() const { return m_shaderState; }
    const UpdateCounter16&		TextureState	() const { return m_textureState; }
    const UpdateCounter16&		ConstantsState	() const { return m_constantsState; }

	bool			NeedsShaderUpdate		( const UpdateTracker16& tracker ) const { return m_shaderState.NeedsUpdate( tracker ); }
	bool			NeedsTextureUpdate		( const UpdateTracker16& tracker ) const { return m_textureState.NeedsUpdate( tracker ); }
	bool			NeedsConstantsUpdate	( const UpdateTracker16& tracker ) const { return m_constantsState.NeedsUpdate( tracker ); }

	bool			UsesConstantBuffer		() const { return m_useConstantBuffer; }

	///@}
};

DEFINE_PTR_TYPE( Brush )


}	// gui
}	// sw

