/**
@file DX11VertexShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"


#include "DX11VertexShader.h"
#include "DX11InputLayout.h"

#include "DX11Compiler.h"

#include "swCommonLib/Common/MemoryLeaks.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11VertexShader >( "sw::DX11VertexShader" );
}


namespace sw
{


// ================================ //
//
DX11VertexShader::DX11VertexShader		( const AssetPath& assetPath, ID3D11VertexShader* shader )
	:	VertexShader( assetPath )
	,	m_vertexShader( shader )
{}

// ================================ //
//
DX11VertexShader::~DX11VertexShader		()
{
	m_vertexShader = nullptr;
}


// ================================ //
//
bool			DX11VertexShader::ReloadFromFile		()
{
	return false;
}

// ================================ //
//
bool			DX11VertexShader::ReloadFromBinFile		()
{
	return false;
}

// ================================ //
//
void            DX11VertexShader::SaveShaderBinFile     ( const fs::Path& fileName )
{}

// ================================ //
//
sw::Nullable< DX11VertexShader* >			DX11VertexShader::CreateFromCode			( const AssetPath& assetPath, const std::string& code, const std::string& entrypoint )
{
	sw::CompilationConfig config( ShaderType::VertexShader );

    if( IsDebugLayerEnabled() )
    {
        config.Debug = true;
    }

	auto result = sw::DX11Compiler::CreateVertexShader( code, entrypoint, config );

	if( !result.IsValid() )
	{
#ifdef _DEBUG
		OutputDebugStringA( result.GetErrorReason().c_str() );
#endif
		return result;
	}

	result.Get()->SetAssetPath( assetPath );

	return result;
}


}	// sw
