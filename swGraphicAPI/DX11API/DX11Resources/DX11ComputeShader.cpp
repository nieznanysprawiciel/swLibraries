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
	rttr::registration::class_< DX11ComputeShader >( "DX11ComputeShader" );
}


// ================================ //
//
DX11ComputeShader::DX11ComputeShader( ID3D11ComputeShader* shader )
{
	m_computeShader = shader;
}

// ================================ //
//
DX11ComputeShader::~DX11ComputeShader()
{
	if( m_computeShader )
		m_computeShader->Release();
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
void			DX11ComputeShader::SaveShaderBinFile	( const std::wstring& fileName )
{

}

// ================================ //
//
DX11ComputeShader*		DX11ComputeShader::CreateFromFile	( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	CompilationConfig config;

#ifdef _DEBUG
	config.Debug = true;
#endif

	auto result = DX11Compiler::CreateComputeShader( fileName, shaderName, shaderModel, config );

#ifdef _DEBUG

	if( !result.IsValid )
	{
		OutputDebugStringA( result.ErrorString.c_str() );
		return nullptr;
	}

#endif

	return result.Value;
}

// ================================ //
//
DX11ComputeShader*		DX11ComputeShader::CreateFromBinFile	( const std::wstring& file_name )
{

	return nullptr;
}


