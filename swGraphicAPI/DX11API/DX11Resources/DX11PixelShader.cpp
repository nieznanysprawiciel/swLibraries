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
DX11PixelShader::DX11PixelShader( ID3D11PixelShader* shader )
{
	m_pixelShader = shader;
}

/**@brief */
DX11PixelShader::~DX11PixelShader()
{
	if( m_pixelShader )
		m_pixelShader->Release();
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
void						DX11PixelShader::SaveShaderBinFile	( const std::wstring& fileName )
{
	assert( false );

}

// ================================ //
//
sw::Nullable< DX11PixelShader* >			DX11PixelShader::CreateFromCode			( const std::wstring& fileName, const std::string& code, const std::string& entrypoint )
{
	sw::CompilationConfig config( ShaderType::PixelShader );

#ifdef _DEBUG
	config.Debug = true;
#endif

	auto result = sw::DX11Compiler::CreatePixelShader( code, entrypoint, config );

	if( !result.IsValid() )
	{
#ifdef _DEBUG
		OutputDebugStringA( result.GetErrorReason().c_str() );
#endif
		return result;
	}

	result.Get()->SetFileName( fileName );
	result.Get()->SetShaderName( entrypoint );

	return result;
}


/**@bref Tworzy obiekt DX11PixelShader na podstawie pliku.

W przypadku błędów kompilacji w trybie debug są one przekierowane do okna Output.

Na razie obsługuje tylko nieskompilowane pliki.
@param[in] fileName Nazwa pliku, z którego zostanie wczytany shader.
@param[in] shaderName Nazwa funkcji, która jest punktem poczatkowym wykonania shadera.
@param[in] shaderModel Łańcuch znaków opisujący shader model.
@return Zwaraca wskaźnik na DX11VertexShader lub nullptr w przypadku błędów wczytywania bądź kompilacji.
*/
DX11PixelShader*			DX11PixelShader::CreateFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	sw::CompilationConfig config( ShaderType::PixelShader );

#ifdef _DEBUG
	config.Debug = true;
#endif

	auto result = sw::DX11Compiler::CreatePixelShader( fileName, shaderName, config );

#ifdef _DEBUG

	if( !result.IsValid() )
	{
		OutputDebugStringA( result.GetErrorReason().c_str() );
		return nullptr;
	}

#endif

	return result.Get();
}

// ================================ //
//
DX11PixelShader*			DX11PixelShader::CreateFromBinFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	return nullptr;
}

}	// sw
