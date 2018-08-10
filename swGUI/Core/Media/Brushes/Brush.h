#pragma once
/**
@file Brush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"


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
	RTTR_REGISTRATION_FRIEND
private:

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

	explicit		Brush		() = default;
	virtual			~Brush		() = default;

	//virtual	BufferPtr	BufferData			() = 0;

	/**@brief Returns file name containing function used in Pixel Shader.
	
	Pixel Shader is combined from shader template and function defined by Brush.*/
	virtual std::string		ShaderFunctionFile	() = 0;

	/**@brief Name of texture to find in resources.*/
	virtual std::string		TextureSource		() = 0;
};

DEFINE_PTR_TYPE( Brush )


}	// gui
}	// sw

