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
	const fs::Path		gBasicPSTemplatePath = "$(CoreGUI-Shader-Dir)/Templates/Basic.psh";
	const fs::Path		gBasicVSTemplatePath = "$(CoreGUI-Shader-Dir)/Templates/Basic.vsh";
    const fs::Path      gOpacityPSTemplatePath = "$(CoreGUI-Shader-Dir)/Templates/Opacity.psh";
    const fs::Path      gOpacityVSTemplatePath = "$(CoreGUI-Shader-Dir)/Templates/Opacity.vsh";
}


// ================================ //
//
ShaderProvider::ShaderProvider		( ResourceManagerAPI resManager, const PathsManager* pathsManager )
	:	m_resourceManager( resManager )
	,	m_pathsManager( pathsManager )
{}

// ================================ //
//
const fs::Path&				        ShaderProvider::GetBasicPSTemplate		() const
{
	return impl::gBasicPSTemplatePath;
}

// ================================ //
//
const fs::Path&				        ShaderProvider::GetBasicVSTemplate		() const
{
	return impl::gBasicVSTemplatePath;
}

// ================================ //
//

const fs::Path&                     ShaderProvider::GetOpacityPSTemplate() const
{
    return impl::gOpacityPSTemplatePath;
}

// ================================ //
//

const fs::Path&                     ShaderProvider::GetOpacityVSTemplate() const
{
    return impl::gOpacityVSTemplatePath;
}

// ================================ //
// At this moment PixelShader and VertexShader generation works the same,
// so we can use common function.
template< typename ShaderType >
inline ResourcePtr< ShaderType >    ShaderProvider::GenerateShader      (   const fs::Path& templatePath,
                                                                            const fs::Path& customFunPath ) const
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
    fs::File::Save( m_pathsManager->Translate( tmpShaderFile.GetFile() ), shaderSource );

    return m_resourceManager.CreateShader< ShaderType >( tmpShaderFile, std::move( shaderSource ) ).Get();
}

// ================================ //
//
PixelShaderPtr          			ShaderProvider::GeneratePS			(	const fs::Path& templatePath,
																			const fs::Path& brushFunPath ) const
{
    return GenerateShader< PixelShader >( templatePath, brushFunPath );
}

// ================================ //
//
VertexShaderPtr         			ShaderProvider::GenerateVS			( const fs::Path& templatePath,
																		  const fs::Path& geomFunPath ) const
{
    return GenerateShader< VertexShader >( templatePath, geomFunPath );
}

// ================================ //
//
std::string							ShaderProvider::BuildShaderSource	(	const fs::Path& templatePath,
																			const fs::Path& brushFunPath ) const
{
	auto templateAbsPath = m_pathsManager->Translate( templatePath );
	auto brushAbsPath = m_pathsManager->Translate( brushFunPath );

	auto templateSource = fs::File::Load( templateAbsPath );
	auto brushSource = fs::File::Load( brushAbsPath );

	return m_shaderBuilder.BuildShader( templateSource, brushSource );
}

}	// gui
}	// sw

