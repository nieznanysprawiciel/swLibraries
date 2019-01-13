#include "swGraphicAPI/DX11API/stdafx.h"
#include "DX11Compiler.h"

#include <d3dcompiler.h>




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
static Nullable< ShaderType* >			CreateShader			( ID3D11Device* device, const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config )
{
	auto result = DX11Compiler::CompileShader( fileName, shaderName, shaderModel, config );

	if( result.IsValid )
	{
		auto compiledShader = result.Value;
		DXShaderType* vertexShader = nullptr;

		HRESULT result = CreateShader< DXShaderType >( device, compiledShader.Get(), &vertexShader );

		if( FAILED( result ) )
			return "Compiling shader [" + Convert::ToString( fileName ) + "], entry point [" + shaderName + "] failed.";

		return new ShaderType( vertexShader );
	}
	else
	{
		return Nullable< ShaderType* >( std::move( result.ErrorString ) );
	}
}


// ================================ //
//
Nullable< DX11VertexShader* >			DX11Compiler::CreateVertexShader		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config )
{
	return CreateShader< DX11VertexShader, ID3D11VertexShader >( device, fileName, shaderName, shaderModel, config );
}

// ================================ //
//
Nullable< DX11PixelShader* >			DX11Compiler::CreatePixelShader			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config )
{
	return CreateShader< DX11PixelShader, ID3D11PixelShader >( device, fileName, shaderName, shaderModel, config );
}

// ================================ //
//
Nullable< DX11ComputeShader* >			DX11Compiler::CreateComputeShader		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig & config )
{
	return CreateShader< DX11ComputeShader, ID3D11ComputeShader >( device, fileName, shaderName, shaderModel, config );
}

// ================================ //
//
Nullable< ComPtr< ID3D10Blob > >		DX11Compiler::CompileShader				( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config  )
{
	ComPtr< ID3D10Blob > compiledShader = nullptr;
	ComPtr< ID3D10Blob > errorBlob = nullptr;

    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
	if( config.Debug )
		flags |= D3DCOMPILE_DEBUG;

	HRESULT hr = D3DCompileFromFile( fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, shaderName.c_str(), shaderModel, flags, 0, &compiledShader, &errorBlob );

	if( FAILED( hr ) )
		return std::string( (char*)errorBlob->GetBufferPointer() );

	return Nullable< ComPtr< ID3D10Blob > >( std::move( compiledShader ) );
}
