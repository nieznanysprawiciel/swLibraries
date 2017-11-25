#pragma once

#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{


/**@brief
@ingroup MockAPI*/
class MockComputeShader : public ComputeShader
{
	RTTR_ENABLE( ComputeShader );
private:
protected:
	~MockComputeShader();
public:
	explicit MockComputeShader		();


	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const std::wstring& fileName ) override;

	static MockComputeShader*		CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "cs_4_0" );
	static MockComputeShader*		CreateFromBinFile		( const std::wstring& fileName );
};

}	// sw
