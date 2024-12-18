#pragma once
/**
@file DX11ComputeShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "DX11Initializer/DX11APIObjects.h"



namespace sw
{



/**@brief DirectX 11 implementation of compute shader.
@ingroup DX11API*/
class DX11ComputeShader : public ComputeShader, protected DX11APIObjects
{
	RTTR_ENABLE( ComputeShader );
private:

	ComPtr< ID3D11ComputeShader >			m_computeShader;

protected:

	virtual		~DX11ComputeShader	();

public:

	explicit	DX11ComputeShader				( const AssetPath& assetPath, ID3D11ComputeShader* shader );

	inline ID3D11ComputeShader*					Get						() { return m_computeShader.Get(); }

	virtual bool								ReloadFromFile			() override;
	virtual bool								ReloadFromBinFile		() override;
	virtual void								SaveShaderBinFile		( const fs::Path& fileName ) override;

	static sw::Nullable< DX11ComputeShader* >	CreateFromCode			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint );

};


}	// sw


