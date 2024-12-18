/**
@file DX11ComputeShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"


#include "DX11ComputeShader.h"
#include "DX11Compiler.h"

#include "swCommonLib/Common/MemoryLeaks.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11ComputeShader >( "sw::DX11ComputeShader" );
}



namespace sw
{


// ================================ //
//
DX11ComputeShader::DX11ComputeShader		( const AssetPath& assetPath, ID3D11ComputeShader* shader )
	:	ComputeShader( assetPath )
	,	m_computeShader( shader )
{}

// ================================ //
//
DX11ComputeShader::~DX11ComputeShader()
{
	m_computeShader = nullptr;
}

// ================================ //
//
bool			DX11ComputeShader::ReloadFromFile		()
{
	return false;
}

// ================================ //
//
bool			DX11ComputeShader::ReloadFromBinFile	()
{
	return false;
}

// ================================ //
//
void			DX11ComputeShader::SaveShaderBinFile	( const fs::Path& fileName )
{}

// ================================ //
//
sw::Nullable< DX11ComputeShader* >		DX11ComputeShader::CreateFromCode		( const AssetPath& fileName, const std::string& code, const std::string& entrypoint )
{
	sw::CompilationConfig config( ShaderType::ComputeShader );

    if( IsDebugLayerEnabled() )
    {
        config.Debug = true;
    }

	auto result = sw::DX11Compiler::CreateComputeShader( code, entrypoint, config );

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
