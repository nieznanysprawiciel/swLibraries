#pragma once
/**
@file IShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/ResourceObject.h"

#include <string>


/**@brief Shader interface.
@ingroup Shaders*/
class IShader : public Resource
{
	RTTR_ENABLE( Resource )
private:
protected:

	std::string				m_shaderEntry;			///< Name of main shader function;
	std::wstring			m_shaderFile;			///< Shader file path.

protected:

	IShader() : Resource( 0 ) {}
	virtual ~IShader() = default;

public:

	const std::wstring&		GetShaderFile			() const		{ return m_shaderFile; }
	const std::string&		GetShaderEntry			() const		{ return m_shaderEntry; }


	virtual bool			ReloadFromFile			() = 0;
	virtual bool			ReloadFromBinFile		() = 0;
	virtual void			SaveShaderBinFile		( const std::wstring& file_name ) = 0;
};

