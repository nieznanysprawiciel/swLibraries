/**
@file RenderTarget.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "RenderTarget.h"


using namespace sw;



RTTR_REGISTRATION
{


	rttr::registration::class_< sw::RenderTarget >( "sw::RenderTarget" )
		.property( "ColorBuffer", &sw::RenderTarget::m_colorBuffer )
		.property( "DepthBuffer", &sw::RenderTarget::m_depthBuffer )
		.property( "StencilBuffer", &sw::RenderTarget::m_stencilBuffer );

}


namespace sw
{



// ================================ //
//
RenderTarget::RenderTarget		( const AssetPath& name, Texture* colorBuffer, Texture* depthBuffer, Texture* stencilBuffer )
	: IRenderTarget( name )
	, m_colorBuffer( colorBuffer )
	, m_depthBuffer( depthBuffer )
	, m_stencilBuffer( stencilBuffer )
{}


// ================================ //
//
RenderTarget::~RenderTarget()
{}





}	// sw





