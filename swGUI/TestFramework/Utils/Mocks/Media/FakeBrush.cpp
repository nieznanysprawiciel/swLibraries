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
	:	Brush( Brush::ConstantBufferMode::Enable )
	,	m_shaderFun( "$(CoreGUI-Shader-Dir)/FakeBrush.ps" )
{}

// ================================ //
//
BufferRange				FakeBrush::BufferData			()
{
	return BufferRange();
}

// ================================ //
//
filesystem::Path		FakeBrush::ShaderFunctionFile	()
{	
	return m_shaderFun;
}

// ================================ //
//
AssetPath			    FakeBrush::TextureSource		()
{
	return m_textureFile;
}

// ================================ //
//
AssetPath   			FakeBrush::ConstantsName		()
{
	return "::FakeBrush-Constants";
}

// ================================ //
//
void					FakeBrush::SetShaderFunction	( const std::string& shaderFun )
{
	m_shaderFun = shaderFun;
	InvalidateShader();
}

// ================================ //
//
void					FakeBrush::SetTextureFile		( const std::string& tex )
{
	m_textureFile = tex;
	InvalidateTexture();
}


}	// gui
}	// sw