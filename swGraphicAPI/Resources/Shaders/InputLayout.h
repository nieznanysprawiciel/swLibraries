#pragma once
/**
@file InputLayout.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/Shaders/IShaderInputLayout.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"



namespace sw
{



/**@brief Class storing vertex shader input layout.
@ingroup Shaders
@ingroup Buffers
@ingroup Resources*/
class ShaderInputLayout : public IShaderInputLayout
{
	RTTR_ENABLE( IShaderInputLayout );
private:
protected:

	virtual			~ShaderInputLayout	() = default;

public:
	explicit		ShaderInputLayout		( const AssetPath& assetPath ) : IShaderInputLayout( assetPath ) {}

public:

    virtual const InputLayoutDescriptor&        GetDescriptor       () const = 0;
};

DEFINE_RESOURCE_PTR_TYPE( ShaderInputLayout );


}	// sw