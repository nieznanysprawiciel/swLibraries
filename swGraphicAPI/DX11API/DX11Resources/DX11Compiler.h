#pragma once
/**
@file DX11Compiler.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "DX11Initializer/DX11APIObjects.h"

#include "swCommonLib/Common/Nullable.h"

#include "DX11Resources/DX11PixelShader.h"
#include "DX11Resources/DX11VertexShader.h"
#include "DX11Resources/DX11ComputeShader.h"


// ================================ //
//
struct CompilationConfig
{
	bool		Debug;


// ================================ //
//
	CompilationConfig()
		: Debug( false )
	{}
};



/**@brief Shader compiler.*/
class DX11Compiler : public DX11APIObjects
{
private:
protected:
public:
	explicit		DX11Compiler		() = default;
	~DX11Compiler	() = default;


	static Nullable< DX11VertexShader* >		CreateVertexShader		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config );
	static Nullable< DX11PixelShader* >			CreatePixelShader		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config );
	static Nullable< DX11ComputeShader* >		CreateComputeShader		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config );

public:

	static Nullable< ComPtr< ID3D10Blob > >		CompileShader			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel, const CompilationConfig& config );
};

