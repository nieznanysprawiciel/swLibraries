#pragma once
/**
@file MockPixelShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{


/**@brief 
@ingroup MockAPI*/
class MockPixelShader : public PixelShader
{
	RTTR_ENABLE( PixelShader );
private:
protected:
	~MockPixelShader();
public:
	MockPixelShader();



	virtual bool						ReloadFromFile			() override;
	virtual bool						ReloadFromBinFile		() override;
	virtual void						SaveShaderBinFile		( const std::wstring& fileName ) override;

	static Nullable< MockPixelShader* >			CreateFromCode			( const std::wstring& fileName, const std::string& code, const std::string& entrypoint );
	static MockPixelShader*						CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static MockPixelShader*						CreateFromBinFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );

	void								SetFileName				( const std::wstring& fileName ) { m_shaderFile = fileName; }
	void								SetShaderName			( const std::string& shaderName ) { m_shaderEntry = shaderName; }
};

}	// sw
