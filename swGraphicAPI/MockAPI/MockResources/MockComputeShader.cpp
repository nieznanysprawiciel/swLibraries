/**
@file MockComputeShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "MockComputeShader.h"




RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockComputeShader >( "sw::MockComputeShader" );
}


namespace sw
{

// ================================ //
//
MockComputeShader::MockComputeShader()
{}

// ================================ //
//
MockComputeShader::~MockComputeShader()
{}

// ================================ //
//
bool MockComputeShader::ReloadFromFile()
{
	return false;
}

// ================================ //
//
bool MockComputeShader::ReloadFromBinFile()
{
	return false;
}

// ================================ //
//
void MockComputeShader::SaveShaderBinFile( const std::wstring& fileName )
{

}

// ================================ //
//
Nullable< MockComputeShader* >		MockComputeShader::CreateFromCode		( const std::wstring& fileName, const std::string& code, const std::string& entrypoint )
{
	if( code.empty() )
		return "Empty shader code.";

	auto shader = new MockComputeShader();
	
	shader->SetFileName( fileName );
	shader->SetShaderName( entrypoint );

	return shader;
}

// ================================ //
//
MockComputeShader*					MockComputeShader::CreateFromFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel )
{
	if( !filesystem::Path( fileName ).Exists() )
		return nullptr;

	return new MockComputeShader();
}

// ================================ //
//
MockComputeShader*					MockComputeShader::CreateFromBinFile		( const std::wstring& file_name )
{

	return nullptr;
}


}	// sw
