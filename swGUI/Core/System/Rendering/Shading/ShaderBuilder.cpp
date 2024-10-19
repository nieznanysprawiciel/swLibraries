/**
@file ShaderBuilder.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "ShaderBuilder.h"


#include <regex>



namespace sw {
namespace gui
{

// ================================ //
//
std::string			ShaderBuilder::BuildShader		( const std::string& shaderTemplate, const std::string& shaderFunction ) const
{
    // Template should contain #UserCode marker. Simply replace with user provided code.
    return std::regex_replace( shaderTemplate, std::regex( "#UserCode" ), shaderFunction );
}


}	// gui
}	// sw