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
// At this moment PixelShader and VertexShader generation works the same,
// so we can use common function.
template< typename ShaderType >
inline ResourcePtr< ShaderType >    ShaderProvider::GenerateShader      (   const filesystem::Path& templatePath,
                                                                            const filesystem::Path& customFunPath ) const
{
    AssetPath tmpShaderFile( fmt::format( "$(TMP)/shaders/{}+{}", templatePath.GetFileName(), customFunPath.GetFileName() ), "main" );

    auto cachedShader = m_resourceManager.GetCached< ShaderType >( tmpShaderFile );
    if( cachedShader )
        return cachedShader;

    // Shader didn't exist, so we must build it.
    auto shaderSource = BuildShaderSource( templatePath, customFunPath );
    if( shaderSource.empty() )
        return nullptr;         /// @todo Better error handling. Maybe we should return Nullable.

    // Note: We save this shader only for debuggins purpose. Shader is created from string.
    filesystem::File::Save( m_pathsManager->Translate( tmpShaderFile.GetFile() ), shaderSource );

    return m_resourceManager.CreateShader< ShaderType >( tmpShaderFile, std::move( shaderSource ) ).Get();
}

// ================================ //
//
PixelShaderPtr          			ShaderProvider::GeneratePS			(	const filesystem::Path& templatePath,
																			const filesystem::Path& brushFunPath ) const
{
    return GenerateShader< PixelShader >( templatePath, brushFunPath );
}

// ================================ //
//
VertexShaderPtr         			ShaderProvider::GenerateVS			( const filesystem::Path& templatePath,
																		  const filesystem::Path& geomFunPath ) const
{
    return GenerateShader< VertexShader >( templatePath, geomFunPath );
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

