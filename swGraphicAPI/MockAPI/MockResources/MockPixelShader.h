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
	virtual				~MockPixelShader		();
public:
	explicit			MockPixelShader			( const AssetPath& name );



	virtual bool						ReloadFromFile			() override;
	virtual bool						ReloadFromBinFile		() override;
	virtual void						SaveShaderBinFile		( const fs::Path& fileName ) override;

	static Nullable< MockPixelShader* >			CreateFromCode			( const AssetPath& name, const std::string& code, const std::string& entrypoint );
};

}	// sw
