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
	virtual void					SaveShaderBinFile		( const fs::Path& fileName ) override;

	static Nullable< MockVertexShader* >		CreateFromCode			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint );
};

}	// sw
