#pragma once
/**
@file DX11VertexShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "DX11Initializer/DX11APIObjects.h"



namespace sw
{


/**@brief DirectX 11 implementation of vertex shader.
@ingroup DX11API*/
class DX11VertexShader : public VertexShader, protected DX11APIObjects
{
	RTTR_ENABLE( VertexShader );
private:

	ComPtr< ID3D11VertexShader >		m_vertexShader;

protected:

	virtual			~DX11VertexShader	();

public:
	explicit		DX11VertexShader	( const AssetPath& assetPath, ID3D11VertexShader* shader );

	inline ID3D11VertexShader*		Get	() { return m_vertexShader.Get(); }


	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const fs::Path& fileName ) override;

	static sw::Nullable< DX11VertexShader* >	CreateFromCode			( const AssetPath& assetPath, const std::string& code, const std::string& entrypoint );
};

}	// sw
