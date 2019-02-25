#pragma once
/**
@file MockComputeShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

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

	virtual		~MockComputeShader		();

public:
	explicit	MockComputeShader		();


	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const std::wstring& fileName ) override;

	static Nullable< MockComputeShader* >		CreateFromCode			( const std::wstring& fileName, const std::string& code, const std::string& entrypoint );
	static MockComputeShader*					CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "cs_4_0" );
	static MockComputeShader*					CreateFromBinFile		( const std::wstring& fileName );

	void								SetFileName				( const std::wstring& fileName ) { m_shaderFile = fileName; }
	void								SetShaderName			( const std::string& shaderName ) { m_shaderEntry = shaderName; }
};

}	// sw
