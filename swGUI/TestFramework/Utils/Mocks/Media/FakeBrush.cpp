/**
@file FakeBrush.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/TestFramework/stdafx.h"
#include "FakeBrush.h"


namespace sw {
namespace gui
{

// ================================ //
//
FakeBrush::FakeBrush()
	:	m_shaderFun( "$(CoreGUI-Shader-Dir)/FakeBrush.ps" )
{}

// ================================ //
//
BufferRange				FakeBrush::BufferData			()
{
	return BufferRange();
}

// ================================ //
//
std::string				FakeBrush::ShaderFunctionFile	()
{	
	return m_shaderFun;
}

// ================================ //
//
std::wstring			FakeBrush::TextureSource		()
{
	return std::wstring();
}

// ================================ //
//
std::wstring			FakeBrush::ConstantsName		()
{
	return L"::FakeBrush-Constants";
}

// ================================ //
//
void					FakeBrush::SetShaderFunction	( const std::string& shaderFun )
{
	m_shaderFun = shaderFun;
	InvalidateShader();
}


}	// gui
}	// sw