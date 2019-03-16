#pragma once
/**
@file IRenderTarget.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/ResourceObject.h"


namespace sw
{


// ================================ //
//
class IRenderTarget : public Resource
{
	RTTR_ENABLE( Resource );
private:
protected:
	IRenderTarget() : Resource( 0 ) {}
	virtual ~IRenderTarget() = default;
public:
};

}	// sw

