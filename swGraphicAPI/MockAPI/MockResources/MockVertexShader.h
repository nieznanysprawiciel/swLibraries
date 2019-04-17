#pragma once
/**
@file MockVertexShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/MeshResources.h"

#include "swCommonLib/Common/Exceptions/Nullable.h"


namespace sw
{


 /**@brief Mock vertex shader implementation.
@ingroup MockAPI*/
class MockVertexShader : public VertexShader
{
	RTTR_ENABLE( VertexShader );
private:
protected:
	~MockVertexShader();
public:
	explicit						MockVertexShader		( const AssetPath& fileName );

	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const std::wstring& fileName ) override;

	static Nullable< MockVertexShader* >		CreateFromCode			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint );
	static MockVertexShader*					CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static MockVertexShader*					CreateFromFile			( const std::wstring& fileName,
																		  const std::string& shaderName,
																		  ShaderInputLayout** layout,
																		  InputLayoutDescriptor* layout_desc,
																		  const char* shaderModel = "vs_4_0" );
	static MockVertexShader*					CreateFromBinFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );

	void										SetShaderName			( const std::string& shaderName ) { m_shaderEntry = shaderName; }
};

}	// sw
