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
protected:

	explicit		IShader		( const AssetPath& assetPath ) : Resource( assetPath ) {}
	virtual			~IShader	() = default;

public:

	virtual bool			ReloadFromFile			() = 0;
	virtual bool			ReloadFromBinFile		() = 0;
	virtual void			SaveShaderBinFile		( const filesystem::Path& fileName ) = 0;
};

}	// sw
