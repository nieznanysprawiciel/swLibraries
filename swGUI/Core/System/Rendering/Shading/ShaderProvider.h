#pragma once
/**
@file ShaderProvider.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/PathsManager.h"

#include "ShaderBuilder.h"



namespace sw {
namespace gui
{

/**@brief Loads and builds shaders.*/
class ShaderProvider
{
private:

	mutable ResourceManagerAPI	m_resourceManager;
	const PathsManager*			m_pathsManager;

	ShaderBuilder				m_shaderBuilder;

protected:
public:

	explicit		ShaderProvider		( ResourceManagerAPI resManager, const PathsManager* pathsManager );
					~ShaderProvider		() = default;

public:

	const fs::Path&			GetBasicPSTemplate		() const;
	const fs::Path&			GetBasicVSTemplate		() const;
    const fs::Path&         GetOpacityPSTemplate	() const;
    const fs::Path&         GetOpacityVSTemplate	() const;

public:

    Nullable< PixelShaderPtr >		GeneratePS				( const fs::Path& templatePath, const fs::Path& brushFunPath ) const;
    Nullable< VertexShaderPtr >		GenerateVS				( const fs::Path& templatePath, const fs::Path& geomFunPath ) const;

	const PathsManager*				GetPathsManager			() const { return m_pathsManager; }

private:

    template< typename ShaderType >
    Nullable< ResourcePtr< ShaderType > >	GenerateShader          ( const fs::Path& templatePath, const fs::Path& customFunPath ) const;

	std::string								BuildShaderSource		( const fs::Path& templatePath, const fs::Path& brushFunPath ) const;
};


}	// gui
}	// sw

