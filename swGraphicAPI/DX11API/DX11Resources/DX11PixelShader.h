#pragma once
/**
@file DX11PixelShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "DX11Initializer/DX11APIObjects.h"


namespace sw
{



/**@brief Implementacja pixel shadera w DirectX 11.
@ingroup DX11API*/
class DX11PixelShader : public PixelShader, protected DX11APIObjects
{
	RTTR_ENABLE( PixelShader );
private:

	ComPtr< ID3D11PixelShader >			m_pixelShader;

protected:
	virtual			~DX11PixelShader			();
public:
	explicit		DX11PixelShader				( const AssetPath& assetPath, ID3D11PixelShader* shader );

	inline ID3D11PixelShader*					Get						() { return m_pixelShader.Get(); }

	virtual bool								ReloadFromFile			() override;
	virtual bool								ReloadFromBinFile		() override;
	virtual void								SaveShaderBinFile		( const fs::Path& fileName ) override;

	static sw::Nullable< DX11PixelShader* >		CreateFromCode			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint );
};

}	// sw
