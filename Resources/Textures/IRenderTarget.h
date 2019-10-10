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

	explicit		IRenderTarget	( const AssetPath& name ) : Resource( name ) {}
	virtual			~IRenderTarget	() = default;

public:
};

}	// sw

