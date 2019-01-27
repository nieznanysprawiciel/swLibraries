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
	,	m_cBuffer( L"::FakeBrush-Constants" )
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
	return m_cBuffer;
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

// ================================ //
//
void					FakeBrush::ChangeConstsBuffer	( const std::wstring& newBuffer )
{
	if( m_cBuffer != newBuffer )
	{
		m_cBuffer = newBuffer;
		InvalidateConstsBuffer();
	}
}


}	// gui
}	// sw