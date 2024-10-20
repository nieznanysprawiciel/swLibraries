#pragma once
/**
@file Brush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Object.h"
#include "swCommonLib/Common/Buffers/BufferRange.h"



/**@defgroup Brushes Brushes
@brief Brushes.
@ingroup Media*/


namespace sw {
namespace gui
{

/**@brief Brush base class.

@todo Reimplement class to allow controls to share brushes.

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
	bool			m_invalidateConstants : 1;
	bool			m_changeCBuffer : 1;
	bool			m_invalidateShader : 1;
	bool			m_invalidateTexture : 1;

protected:

	///@name Derived classes API
	///@{

	void			InvalidateConstants		();
	void			InvalidateShader		();
	void			InvalidateTexture		();
	void			InvalidateConstsBuffer	();

	///@}

public:

	explicit		Brush		( ConstantBufferMode enableCB );
	virtual			~Brush		() = default;

	/**@brief Returns BufferRange of new content of constant buffer.
	@note Brush object is still owner of returned memory and it shouldn't be freed after return from this function.
	It is recommended to use @ref StackBuffer in Brush implementation.*/
	virtual	BufferRange		    BufferData			() = 0;

	/**@brief Returns file name containing function used in Pixel Shader.
	
	Pixel Shader is combined from shader template and function defined by Brush.*/
	virtual filesystem::Path	ShaderFunctionFile	() = 0;

	/**@brief Name of texture to find in resources.*/
	virtual AssetPath	        TextureSource		() = 0;

	/**@brief Returns key used to store/find contant buffer in resources.*/
	virtual AssetPath	        ConstantsName		() = 0;

private:

	///@name RenderingSystem API
	///@{

	void			ShaderUpdated		();
	void			TextureUpdated		();
	void			ConstantsUpdated	();
	void			BufferChanged		();

protected:

	bool			NeedsShaderUpdate		() const { return m_invalidateShader; }
	bool			NeedsTextureUpdate		() const { return m_invalidateTexture; }
	bool			NeedsConstantsUpdate	() const { return m_invalidateConstants; }
	bool			NeedsBufferChange		() const { return m_changeCBuffer; }

	bool			UsesConstantBuffer		() const { return m_useConstantBuffer; }

	///@}
};

DEFINE_PTR_TYPE( Brush )


}	// gui
}	// sw

