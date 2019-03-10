#pragma once
/**
@file InputLayout.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/Shaders/IShaderInputLayout.h"
#include "swCommonLib/Common/ObjectDeleter.h"




namespace sw
{



/**@brief Class storing vertex shader input layout.
@ingroup Shaders
@ingroup Buffers
@ingroup Resources*/
class ShaderInputLayout : public IShaderInputLayout
{
	RTTR_ENABLE( IShaderInputLayout );
	friend ObjectDeleter< ShaderInputLayout >;
private:
protected:

	virtual			~ShaderInputLayout	() = default;

public:
	explicit		ShaderInputLayout	() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};



}	// sw