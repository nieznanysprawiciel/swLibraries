#pragma once
/**
@file ShaderProvider.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/Resources/MeshResources.h"

#include "swGUI/Core/System/Config/PathsManager.h"
#include "ShaderBuilder.h"



namespace sw {
namespace gui
{

/**@brief Loads and builds shaders.*/
class ShaderProvider
{
private:

	mutable ResourceManager*	m_resourceManager;
	const PathsManager*			m_pathsManager;

	ShaderBuilder				m_shaderBuilder;

protected:
public:

	explicit		ShaderProvider		( ResourceManager* resManager, const PathsManager* pathsManager );
					~ShaderProvider		() = default;

public:

	const filesystem::Path&			GetBasicPSTemplate		() const;
	const filesystem::Path&			GetBasicVSTemplate		() const;

public:

	ResourcePtr< PixelShader >		GeneratePS				( const filesystem::Path& templatePath, const filesystem::Path& brushFunPath ) const;
	ResourcePtr< VertexShader >		GenerateVS				( const filesystem::Path& templatePath, const filesystem::Path& geomFunPath ) const;

	const PathsManager*				GetPathsManager			() const { return m_pathsManager; }

private:

	std::string						BuildShaderSource		( const filesystem::Path& templatePath, const filesystem::Path& brushFunPath ) const;
};


}	// gui
}	// sw

