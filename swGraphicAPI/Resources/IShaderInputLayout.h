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
	IShaderInputLayout() : Resource( 0 ) {}
	virtual ~IShaderInputLayout() = default;
public:

};

}	// sw
