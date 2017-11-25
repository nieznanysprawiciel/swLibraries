#pragma once

#include "swGraphicAPI/Resources/MeshResources.h"


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
	MockVertexShader();

	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const std::wstring& fileName ) override;

	static MockVertexShader*		CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static MockVertexShader*		CreateFromFile			( const std::wstring& fileName,
															  const std::string& shaderName,
															  ShaderInputLayout** layout,
															  InputLayoutDescriptor* layout_desc,
															  const char* shaderModel = "vs_4_0" );
	static MockVertexShader*		CreateFromBinFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );

	void							SetFileName				( const std::wstring& fileName ) { m_shaderFile = fileName; }
	void							SetShaderName			( const std::string& shaderName ) { m_shaderEntry = shaderName; }
};

}	// sw
