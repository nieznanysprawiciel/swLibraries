/**
@file RenderingSystem.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "RenderingSystem.h"



namespace sw {
namespace gui
{


// ================================ //
//
RenderingSystem::RenderingSystem			( ResourceManager* resourceManager, PathsManager* pathsManager, IRendererOPtr&& renderer )
	:	m_resourceManager( resourceManager )
	,	m_renderer( std::move( renderer ) )
	,	m_shaderProvider( resourceManager, pathsManager )
{}

// ================================ //
//
void				RenderingSystem::RenderTree			( HostWindow* host )
{


}

// ================================ //
//
void				RenderingSystem::InitializeGraphicState		( ResourceManager* rm )
{
	m_rasterizerState = rm->CreateRasterizerState( L"sw::gui::DefaultRasterizerState", RasterizerStateInfo() );

	DepthStencilInfo depthDesc;
	depthDesc.EnableDepthTest = false;		// Painter algorithm. We never check depth value and always write new pixel.
	depthDesc.EnableStencilTest = false;

	m_depthState = rm->CreateDepthStencilState( L"sw::gui::DefaultDepthState", depthDesc );

	BlendingInfo blendDesc;
	blendDesc.EnableBlending = true;
	/// @todo We should set blend operation here.

	m_transparentBlendState = rm->CreateBlendingState( L"sw::gui::TransparentBlendState", blendDesc );

	blendDesc.EnableBlending = false;

	m_opaqueBlendState = rm->CreateBlendingState( L"sw::gui::OpaqueBlendState", blendDesc );
}


}	// gui
}	// sw
