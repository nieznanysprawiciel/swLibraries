#pragma once
/**
@file IShader.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.
*/


#include "swGraphicAPI/Resources/ResourceObject.h"



class IShaderInputLayout : public Resource
{
	RTTR_ENABLE( Resource );
private:
protected:
	IShaderInputLayout() : Resource( 0 ) {}
	virtual ~IShaderInputLayout() = default;
public:

};

