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
	explicit	MockComputeShader		( const AssetPath& fileName );


	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const fs::Path& fileName ) override;

	static Nullable< MockComputeShader* >		CreateFromCode			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint );
};

}	// sw
