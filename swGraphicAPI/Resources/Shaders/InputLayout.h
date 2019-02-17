#pragma once
/**
@file InputLayout.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/IShaderInputLayout.h"
#include "swCommonLib/Common/ObjectDeleter.h"


/**@brief Klasa przechowuje layout wierzcho³ka trafiaj¹cego do
vertex shadera.
@ingroup Shaders
@ingroup Buffers
@ingroup Resources*/
class ShaderInputLayout : public IShaderInputLayout
{
	RTTR_ENABLE( IShaderInputLayout );
	friend ObjectDeleter< ShaderInputLayout >;
private:
protected:
	virtual ~ShaderInputLayout() = default;
public:
	ShaderInputLayout() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};


