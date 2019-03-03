#pragma once
/**
@file DX11InputLayout.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"
#include "DX11Initializer/DX11APIObjects.h"



/**@brief DirectX 11 implementation of input layout.
@ingroup DX11API*/
class DX11InputLayout : public ShaderInputLayout, protected DX11APIObjects
{
	RTTR_ENABLE( ShaderInputLayout );
private:

	ID3D11InputLayout*				m_vertexLayout;

protected:

	virtual			~DX11InputLayout		();

public:

	explicit									DX11InputLayout		( ID3D11InputLayout* layout );

	static sw::Nullable< DX11InputLayout* >		CreateLayout		( const InputLayoutDescriptor& layoutDesc );

public:

	inline ID3D11InputLayout*					Get					() { return m_vertexLayout; }
};

