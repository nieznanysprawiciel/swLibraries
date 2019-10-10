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


namespace sw
{

// ================================ //
//
struct ShaderModelDesc
{
	ShaderType	Type;
	uint8		Major;
	uint8		Minor;

// ================================ //
//
	ShaderModelDesc( ShaderType type )
		: Major( 5 )
		, Minor( 0 )
		, Type( type )
	{}

// ================================ //
//
	std::string		ToString		() const;
};


// ================================ //
//
struct CompilationConfig
{
	ShaderModelDesc		ShaderModel;
	bool				Debug;


// ================================ //
//
	CompilationConfig( ShaderType shaderType )
		: Debug( false )
		, ShaderModel( shaderType )
	{}
};



/**@brief Shader compiler.
@ingroup DX11API*/
class DX11Compiler : public DX11APIObjects
{
private:
protected:
public:
	explicit		DX11Compiler		() = default;
	~DX11Compiler		() = default;


	static Nullable< DX11VertexShader* >		CreateVertexShader		( const std::string& code, const std::string& entrypoint, const CompilationConfig& config );
	static Nullable< DX11PixelShader* >			CreatePixelShader		( const std::string& code, const std::string& entrypoint, const CompilationConfig& config );
	static Nullable< DX11ComputeShader* >		CreateComputeShader		( const std::string& code, const std::string& entrypoint, const CompilationConfig& config );


	static Nullable< DX11VertexShader* >		CreateVertexShader		( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config );
	static Nullable< DX11PixelShader* >			CreatePixelShader		( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config );
	static Nullable< DX11ComputeShader* >		CreateComputeShader		( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config );

public:

	static Nullable< ComPtr< ID3D10Blob > >		CompileShader			( const std::wstring& fileName, const std::string& shaderName, const CompilationConfig& config );
	static Nullable< ComPtr< ID3D10Blob > >		CompileShader			( const std::string& code, const std::string& entrypoint, const CompilationConfig& config );
};


}	// sw

