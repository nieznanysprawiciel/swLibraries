/**
@file ShaderProvider.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "ShaderProvider.h"

#include "swCommonLib/System/File.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"



namespace sw {
namespace gui
{


namespace impl
{
	const filesystem::Path		gBasicPSTemplatePath = "$(CoreGUI-Shader-Dir)/Templates/Basic.psh";
	const filesystem::Path		gBasicVSTemplatePath = "$(CoreGUI-Shader-Dir)/Templates/Basic.vsh";
}


// ================================ //
//
ShaderProvider::ShaderProvider		( ResourceManagerAPI resManager, const PathsManager* pathsManager )
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
const filesystem::Path&				ShaderProvider::GetBasicVSTemplate		() const
{
	return impl::gBasicVSTemplatePath;
}

// ================================ //
//
PixelShaderPtr          			ShaderProvider::GeneratePS			(	const filesystem::Path& templatePath,
																			const filesystem::Path& brushFunPath ) const
{
	auto shaderSource = BuildShaderSource( templatePath, brushFunPath );
	if( shaderSource.empty() )
		return nullptr;         /// @todo Better error handling. Maybe we should return Nullable.

	// Note: We save this shader only for debuggins purpose. Shader is created from string.
	filesystem::Path tmpShaderFile = m_pathsManager->Translate( "$(TMP)/shaders/" + templatePath.GetFileName() + "+" + brushFunPath.GetFileName() );
	filesystem::File::Save( tmpShaderFile, shaderSource );
	
	return m_resourceManager.CreatePixelShader( AssetPath( tmpShaderFile, "main" ), std::move( shaderSource ) ).Get();
}

// ================================ //
//
VertexShaderPtr         			ShaderProvider::GenerateVS			( const filesystem::Path& templatePath,
																		  const filesystem::Path& geomFunPath ) const
{
	auto shaderSource = BuildShaderSource( templatePath, geomFunPath );
	if( shaderSource.empty() )
        return nullptr;         /// @todo Better error handling. Maybe we should return Nullable.

    // Note: We save this shader only for debuggins purpose. Shader is created from string.
	filesystem::Path tmpShaderFile = m_pathsManager->Translate( "$(TMP)/shaders/" + templatePath.GetFileName() + "+" + geomFunPath.GetFileName() );
	filesystem::File::Save( tmpShaderFile, shaderSource );
	
    return m_resourceManager.CreateVertexShader( AssetPath( tmpShaderFile, "main" ), std::move( shaderSource ) ).Get();
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

