/**
@file ShaderProvider.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "ShaderProvider.h"

#include "swCommonLib/System/File.h"



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

	assert( !"Implement me" );

	return ResourcePtr< PixelShader >();
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

