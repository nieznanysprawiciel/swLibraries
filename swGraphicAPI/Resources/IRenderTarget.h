#pragma once
/**
@file IRenderTarget.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "ResourceObject.h"

class IRenderTarget : public ResourceObject
{
	RTTR_ENABLE( ResourceObject );
private:
protected:
	IRenderTarget() : ResourceObject( 0 ) {}
	virtual ~IRenderTarget() = default;
public:
};