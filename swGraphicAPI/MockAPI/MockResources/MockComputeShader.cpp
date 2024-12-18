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
MockComputeShader::MockComputeShader( const AssetPath& fileName )
	:	ComputeShader( fileName )
{}

// ================================ //
//
MockComputeShader::~MockComputeShader()
{}

// ================================ //
//
bool                                MockComputeShader::ReloadFromFile       ()
{
	return false;
}

// ================================ //
//
bool                                MockComputeShader::ReloadFromBinFile    ()
{
	return false;
}

// ================================ //
//
void                                MockComputeShader::SaveShaderBinFile    ( const fs::Path& fileName )
{

}

// ================================ //
//
Nullable< MockComputeShader* >		MockComputeShader::CreateFromCode		( const AssetPath& fileName, const std::string& code, const std::string& entrypoint )
{
	if( code.empty() )
		return "Empty shader code.";

	auto shader = new MockComputeShader( fileName );
	
	shader->SetAssetPath( fileName );

	return shader;
}


}	// sw
