/**
@file DX11PixelShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11PixelShader.h"
#include "DX11Compiler.h"

#include "swCommonLib/Common/MemoryLeaks.h"


//====================================================================================//
//			RTTR registration	
//====================================================================================//

RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11PixelShader >( "sw::DX11PixelShader" );
}


//====================================================================================//
//			DX11PixelShader	
//====================================================================================//


namespace sw
{


/**@brief */
DX11PixelShader::DX11PixelShader		( const AssetPath& assetPath, ID3D11PixelShader* shader )
	:	PixelShader( assetPath )
	,	m_pixelShader( shader )
{}

/**@brief */
DX11PixelShader::~DX11PixelShader()
{
	m_pixelShader = nullptr;
}

/**@brief */
bool						DX11PixelShader::ReloadFromFile()
{
	return false;
}

/**@brief */
bool						DX11PixelShader::ReloadFromBinFile()
{
	return false;
}

/**@brief */
void						DX11PixelShader::SaveShaderBinFile	( const fs::Path& fileName )
{}

// ================================ //
//
sw::Nullable< DX11PixelShader* >			DX11PixelShader::CreateFromCode			( const AssetPath& fileName, const std::string& code, const std::string& entrypoint )
{
	sw::CompilationConfig config( ShaderType::PixelShader );

    if( IsDebugLayerEnabled() )
    {
        config.Debug = true;
    }

	auto result = sw::DX11Compiler::CreatePixelShader( code, entrypoint, config );

	if( !result.IsValid() )
	{
#ifdef _DEBUG
		OutputDebugStringA( result.GetErrorReason().c_str() );
#endif
		return result;
	}

	result.Get()->SetAssetPath( fileName );

	return result;
}



}	// sw
