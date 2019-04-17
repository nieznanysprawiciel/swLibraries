#pragma once
/**
@file IShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/ResourceObject.h"

#include <string>



namespace sw
{

/**@brief Shader interface.
@ingroup Shaders*/
class IShader : public Resource
{
	RTTR_ENABLE( Resource )
private:
protected:

	std::string				m_shaderEntry;			///< Name of main shader function;

protected:

	explicit		IShader		( const AssetPath& assetPath ) : Resource( assetPath ) {}
	virtual			~IShader	() = default;

public:

	const std::string&		GetShaderEntry			() const { return m_shaderEntry; }


	virtual bool			ReloadFromFile			() = 0;
	virtual bool			ReloadFromBinFile		() = 0;
	virtual void			SaveShaderBinFile		( const std::wstring& file_name ) = 0;
};

}	// sw
