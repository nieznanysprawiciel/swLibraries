/**
@file MockVertexShader.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "MockVertexShader.h"

#include "MockInputLayout.h"

#include "swCommonLib/System/Path.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockVertexShader >( "sw::MockVertexShader" );
}


namespace sw
{

// ================================ //
//
MockVertexShader::MockVertexShader	( const AssetPath& name )
	:	VertexShader( name )
{}

// ================================ //
//
MockVertexShader::~MockVertexShader()
{}


// ================================ //
//
bool			MockVertexShader::ReloadFromFile	()
{
	return false;
}

// ================================ //
//
bool			MockVertexShader::ReloadFromBinFile	()
{
	return false;
}

// ================================ //
//
void			MockVertexShader::SaveShaderBinFile	( const fs::Path& file_name )
{}

// ================================ //
//
Nullable< MockVertexShader* >			MockVertexShader::CreateFromCode		( const AssetPath& name, const std::string& code, const std::string& entrypoint )
{
	if( code.empty() )
		return "Empty shader code.";

	return new MockVertexShader( name );
}



}	// sw
