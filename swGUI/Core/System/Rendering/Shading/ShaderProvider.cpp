/**
@file ShaderProvider.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "ShaderProvider.h"

#include "swCommonLib/System/File.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"



namespace sw {
namespace gui
{


namespace impl
{
	const filesystem::Path		gBasicPSTemplatePath = "$(CoreGUI-Shader-Dir)/Templates/Basic.ps";
}


// ================================ //
//
ShaderProvider::ShaderProvider		( ResourceManager* resManager, const PathsManager* pathsManager )
	:	m_resourceManager( resManager )
	,	m_pathsManager( pathsManager )
{}

// ================================ //
//
const filesystem::Path&				ShaderProvider::GetBasicPSTemplate		() const
{
	return impl::gBasicPSTemplatePath;
}

// ================================ //
//
ResourcePtr< PixelShader >			ShaderProvider::GeneratePS			(	const filesystem::Path& templatePath,
																			const filesystem::Path& brushFunPath ) const
{
	auto shaderSource = BuildShaderSource( templatePath, brushFunPath );
	if( shaderSource.empty() )
		return nullptr;

	// @todo Note that we could create shader from string, if ResourceManager API would support such things.
	// This feature will come in next more generic version of ResourceManager. For now we must be satisfied with this solution.
	filesystem::Path tmpShaderFile = m_pathsManager->Translate( "$(TMP)/shaders/" + templatePath.GetFileName() + "+" + brushFunPath.GetFileName() );
	filesystem::File::Save( tmpShaderFile, shaderSource );
	
	return m_resourceManager->LoadPixelShader( tmpShaderFile.WString(), "main" );
}

// ================================ //
//
ResourcePtr< VertexShader >			ShaderProvider::GenerateVS			( const filesystem::Path& templatePath,
																		  const filesystem::Path& geomFunPath ) const
{
	auto shaderSource = BuildShaderSource( templatePath, geomFunPath );
	if( shaderSource.empty() )
		return nullptr;

	// @todo Note that we could create shader from string, if ResourceManager API would support such things.
	// This feature will come in next more generic version of ResourceManager. For now we must be satisfied with this solution.
	filesystem::Path tmpShaderFile = m_pathsManager->Translate( "$(TMP)/shaders/" + templatePath.GetFileName() + "+" + geomFunPath.GetFileName() );
	filesystem::File::Save( tmpShaderFile, shaderSource );
	
	return m_resourceManager->LoadVertexShader( tmpShaderFile.WString(), "main" );
}

// ================================ //
//
std::string							ShaderProvider::BuildShaderSource	(	const filesystem::Path& templatePath,
																			const filesystem::Path& brushFunPath ) const
{
	auto templateAbsPath = m_pathsManager->Translate( templatePath );
	auto brushAbsPath = m_pathsManager->Translate( brushFunPath );

	auto templateSource = filesystem::File::Load( templateAbsPath );
	auto brushSource = filesystem::File::Load( brushAbsPath );

	return m_shaderBuilder.BuildShader( templateSource, brushSource );
}

}	// gui
}	// sw

