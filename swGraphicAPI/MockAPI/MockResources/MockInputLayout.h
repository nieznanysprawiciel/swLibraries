#pragma once
/**
@file MockInputLayout.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.
*/

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{


/**@brief 
@ingroup MockAPI*/
class MockInputLayout : public ShaderInputLayout
{
	RTTR_ENABLE( ShaderInputLayout );
private:
protected:
	~MockInputLayout();
public:
	MockInputLayout();

};

}	// sw
