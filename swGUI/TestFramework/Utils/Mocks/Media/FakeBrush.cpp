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
	:	Brush( Brush::EnableConstantBuffer::True )
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
std::string				FakeBrush::ShaderFunctionFile	()
{	
	return m_shaderFun;
}

// ================================ //
//
std::wstring			FakeBrush::TextureSource		()
{
	return m_textureFile;
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

// ================================ //
//
void					FakeBrush::SetTextureFile		( const std::wstring& tex )
{
	m_textureFile = tex;
	InvalidateTexture();
}


}	// gui
}	// sw