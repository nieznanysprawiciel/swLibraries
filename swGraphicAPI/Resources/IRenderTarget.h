#pragma once
/**
@file IRenderTarget.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.
*/

#include "ResourceObject.h"

class IRenderTarget : public Resource
{
	RTTR_ENABLE( Resource );
private:
protected:
	IRenderTarget() : Resource( 0 ) {}
	virtual ~IRenderTarget() = default;
public:
};