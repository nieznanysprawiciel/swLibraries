#pragma once
/**
@file ShaderBuilder.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <string>


namespace sw {
namespace gui
{

// ================================ //
//
class ShaderBuilder
{
private:

public:

	std::string			BuildShader		( const std::string& shaderTemplate, const std::string& shaderFunction );

};




}	// gui
}	// sw


