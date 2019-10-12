/**
@file DX11Compiler.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/DX11API/stdafx.h"
#include "DX11Compiler.h"
#include "swGraphicAPI/DX11API/DX11Initializer/DX11Utils.h"


#include <d3dcompiler.h>

#include "swCommonLib/Common/Converters.h"
#include "swCommonLib/System/File.h"

#include "swGraphicAPI/Resources/Shaders/Exceptions/CompilationException.h"



namespace sw
{

//====================================================================================//
//			Template for choosing shader creation function.	
//====================================================================================//

// ================================ //
//
template< typename DXShaderType >
HRESULT									CreateShader						( ID3D11Device* device, ID3D10Blob* compiledShader, DXShaderType** shader )
{
	assert( false ); return 0;
}

// ================================ //
//
template<>
HRESULT									CreateShader< ID3D11VertexShader >	( ID3D11Device* device, ID3D10Blob* compiledShader, ID3D11VertexShader** shader )
{
	return device->CreateVertexShader( compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, shader );
}

// ================================ //
//
template<>
HRESULT									CreateShader< ID3D11PixelShader >	( ID3D11Device* device, ID3D10Blob* compiledShader, ID3D11PixelShader** shader )
{
	return device->CreatePixelShader( compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, shader );
}

// ================================ //
//
template<>
HRESULT									CreateShader< ID3D11ComputeShader >	( ID3D11Device* device, ID3D10Blob* compiledShader, ID3D11ComputeShader** shader )
{
	return device->CreateComputeShader( compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), nullptr, shader );
}

//====================================================================================//
//			Compiling	
//====================================================================================//

// ================================ //
//
template< typename ShaderType, typename DXShaderType >
static Nullable< ShaderType* >			CreateShader			( ID3D11Device* device, const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config )
{
	std::string code = filesystem::File::Load( fileName );
	return CreateShader< ShaderType, DXShaderType >( device, code, shaderName, config );
}

// ================================ //
//
template< typename ShaderType, typename DXShaderType >
static Nullable< ShaderType* >			CreateShader			( ID3D11Device* device, const std::string& code, const std::string& entrypoint, const CompilationConfig& config )
{
	auto compilationResult = DX11Compiler::CompileShader( code, entrypoint, config );

	if( compilationResult.IsValid() )
	{
		auto compiledShader = compilationResult.Get();
		DXShaderType* shader = nullptr;

		HRESULT result = CreateShader< DXShaderType >( device, compiledShader.Get(), &shader );

		if( FAILED( result ) )
            return fmt::format( "[DX11Compiler] Creating shader failed. {}", DX11Utils::ErrorString( result ) );

		return new ShaderType( AssetPath( "", "" ), shader );
	}
	else
	{
		return Nullable< ShaderType* >( std::move( compilationResult.GetError() ) );
	}
}

// ================================ //
//
Nullable< DX11VertexShader* >			DX11Compiler::CreateVertexShader			( const std::string& code, const std::string& entrypoint, const CompilationConfig& config )
{
	return CreateShader< DX11VertexShader, ID3D11VertexShader >( device, code, entrypoint, config );
}

// ================================ //
//
Nullable< DX11PixelShader* >			DX11Compiler::CreatePixelShader				( const std::string& code, const std::string& entrypoint, const CompilationConfig& config )
{
	return CreateShader< DX11PixelShader, ID3D11PixelShader >( device, code, entrypoint, config );
}

// ================================ //
//
Nullable< DX11ComputeShader* >			DX11Compiler::CreateComputeShader			( const std::string& code, const std::string& entrypoint, const CompilationConfig& config )
{
	return CreateShader< DX11ComputeShader, ID3D11ComputeShader >( device, code, entrypoint, config );
}

// ================================ //
//
Nullable< DX11VertexShader* >			DX11Compiler::CreateVertexShader		( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config )
{
	return CreateShader< DX11VertexShader, ID3D11VertexShader >( device, fileName, shaderName, config );
}

// ================================ //
//
Nullable< DX11PixelShader* >			DX11Compiler::CreatePixelShader			( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config )
{
	return CreateShader< DX11PixelShader, ID3D11PixelShader >( device, fileName, shaderName, config );
}

// ================================ //
//
Nullable< DX11ComputeShader* >			DX11Compiler::CreateComputeShader		( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig & config )
{
	return CreateShader< DX11ComputeShader, ID3D11ComputeShader >( device, fileName, shaderName, config );
}

// ================================ //
//
Nullable< ComPtr< ID3D10Blob > >		DX11Compiler::CompileShader				( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config )
{
	std::string code = filesystem::File::Load( fileName );
	return CompileShader( code, shaderName, config );
}

// ================================ //
//
Nullable< ComPtr< ID3D10Blob > >		DX11Compiler::CompileShader				( const std::string& code, const std::string& entrypoint, const CompilationConfig& config )
{
	ComPtr< ID3D10Blob > compiledShader = nullptr;
	ComPtr< ID3D10Blob > errorBlob = nullptr;

	UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
	if( config.Debug )
		flags |= D3DCOMPILE_DEBUG;

	std::string shaderModel = config.ShaderModel.ToString();

	HRESULT hr = D3DCompile( code.c_str(), code.size(), nullptr, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypoint.c_str(), shaderModel.c_str(), flags, 0, &compiledShader, &errorBlob );

	if( FAILED( hr ) )
		return CompilationException::Create( (char*)errorBlob->GetBufferPointer() );

	return Nullable< ComPtr< ID3D10Blob > >( std::move( compiledShader ) );
}


namespace impl
{

// ================================ //
//
std::string								ShaderTypeToString						( ShaderType type )
{
	switch( type )
	{
		case ShaderType::VertexShader:
			return "vs";
		case ShaderType::PixelShader:
			return "ps";
		case ShaderType::ComputeShader:
			return "cs";
		case ShaderType::GeometryShader:
			return "gs";
		case ShaderType::TesselationControlShader:
			return "hs";
		case ShaderType::TesselationEvaluationShader:
			return "ds";
	}
	return "";
}

}	// impl


// ================================ //
//
std::string								ShaderModelDesc::ToString				() const
{
	return impl::ShaderTypeToString( this->Type ) + "_" + Convert::ToString( this->Major ) + "_" + Convert::ToString( this->Minor );
}

}	// sw

