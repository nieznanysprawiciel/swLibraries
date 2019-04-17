#pragma once
/**
@file IShaderInputLayout.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/Resources/ResourceObject.h"




namespace sw
{

// ================================ //
//
class IShaderInputLayout : public Resource
{
	RTTR_ENABLE( Resource );
private:
protected:
	explicit		IShaderInputLayout		( const AssetPath& assetPath ) : Resource( assetPath ) {}
	virtual			~IShaderInputLayout		() = default;
public:

};

}	// sw
