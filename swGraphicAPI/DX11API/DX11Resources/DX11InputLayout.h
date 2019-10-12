#pragma once
/**
@file DX11InputLayout.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"
#include "DX11Initializer/DX11APIObjects.h"



namespace sw
{


/**@brief DirectX 11 implementation of input layout.
@ingroup DX11API*/
class DX11InputLayout : public ShaderInputLayout, protected DX11APIObjects
{
	RTTR_ENABLE( ShaderInputLayout );
private:

	ComPtr< ID3D11InputLayout >			m_vertexLayout;
    InputLayoutDescriptor               m_descriptor;

protected:

	virtual			~DX11InputLayout		();

public:

	explicit									DX11InputLayout		( const AssetPath& fileName, ID3D11InputLayout* layout, InputLayoutDescriptor desc );
    
    static sw::Nullable< DX11InputLayout* >		CreateLayout		( const AssetPath& fileName, const InputLayoutDescriptor& layoutDesc );

public:

	inline ID3D11InputLayout*					Get					() { return m_vertexLayout.Get(); }

    virtual const InputLayoutDescriptor&        GetDescriptor       () const override;
};

}	// sw
