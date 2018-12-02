#pragma once
/**
@file Brush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"
#include "swCommonLib/Common/Buffers/BufferRange.h"



/**@defgroup Brushes Brushes
@brief Brushes.
@ingroup Media*/


namespace sw {
namespace gui
{

/**@brief Brush base class.
@ingroup Brushes*/
class Brush : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND;

	friend class Drawing;
	friend class RenderingSystem;

public:

	enum class EnableConstantBuffer
	{
		True,
		False
	};

private:

	bool			m_useConstantBuffer : 1;
	bool			m_invalidateConstants : 1;
	bool			m_invalidateShader : 1;
	bool			m_invalidateTexture : 1;

protected:

	///@name Derived classes API
	///@{

	void			InvalidateConstants		();
	void			InvalidateShader		();
	void			InvalidateTexture		();

	///@}

public:

	explicit		Brush		( EnableConstantBuffer enableCB );
	virtual			~Brush		() = default;

	/**@brief Returns BufferRange of new content of constant buffer.
	@note Brush object is still owner of returned memory and it shouldn't be freed after return from this function.
	It is recommended to use @ref StackBuffer in Brush implementation.*/
	virtual	BufferRange		BufferData			() = 0;

	/**@brief Returns file name containing function used in Pixel Shader.
	
	Pixel Shader is combined from shader template and function defined by Brush.*/
	virtual std::string		ShaderFunctionFile	() = 0;

	/**@brief Name of texture to find in resources.*/
	virtual std::wstring	TextureSource		() = 0;

	/**@brief Returns key used to store/find contant buffer in resources.*/
	virtual std::wstring	ConstantsName		() = 0;

private:

	///@name RenderingSystem API
	///@{

	void			ShaderUpdated		();
	void			TextureUpdated		();
	void			ConstantsUpdated	();

protected:

	bool			NeedsShaderUpdate		() const { return m_invalidateShader; }
	bool			NeedsTextureUpdate		() const { return m_invalidateTexture; }
	bool			NeedsConstantsUpdate	() const { return m_invalidateConstants; }

	bool			UsesConstantBuffer		() const { return m_useConstantBuffer; }

	///@}
};

DEFINE_PTR_TYPE( Brush )


}	// gui
}	// sw

