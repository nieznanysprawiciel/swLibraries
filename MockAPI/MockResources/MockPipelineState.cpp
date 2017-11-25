/**
@file DX11PipelineState.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "MockPipelineState.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockRasterizerState >( "sw::MockRasterizerState" );
	rttr::registration::class_< sw::MockDepthStencilState >( "sw::MockDepthStencilState" );
	rttr::registration::class_< sw::MockBlendingState >( "sw::MockBlendingState" );
}

namespace sw
{


//====================================================================================//
//			RasterizerState	
//====================================================================================//

MockRasterizerState::MockRasterizerState( const RasterizerStateInfo& info )
	:	m_info( info )
{}

// ================================ //
//
std::string						MockRasterizerState::GetResourceName() const
{
	return std::string();
}

// ================================ //
//
const RasterizerStateInfo&		MockRasterizerState::GetDescriptor()
{
	return m_info;
}

// ================================ //
//
MockRasterizerState*			MockRasterizerState::Create		( const RasterizerStateInfo& info )
{
	return new MockRasterizerState( info );
}



//====================================================================================//
//			DepthStencilState	
//====================================================================================//

MockDepthStencilState::MockDepthStencilState( const DepthStencilInfo& info )
	:	m_info( info )
{}

// ================================ //
//
std::string						MockDepthStencilState::GetResourceName() const
{
	return std::string();
}

// ================================ //
//
const DepthStencilInfo&			MockDepthStencilState::GetDescriptor()
{
	return m_info;
}

// ================================ //
//
MockDepthStencilState*			MockDepthStencilState::Create			( const DepthStencilInfo& info )
{
	return new MockDepthStencilState( info );
}



//====================================================================================//
//			BlendingState	
//====================================================================================//

MockBlendingState::MockBlendingState( const BlendingInfo& info )
	:	m_info( info )
{}

// ================================ //
//
std::string						MockBlendingState::GetResourceName() const
{
	return std::string();
}

// ================================ //
//
const BlendingInfo&				MockBlendingState::GetDescriptor()
{
	return m_info;
}

MockBlendingState*				MockBlendingState::Create		( const BlendingInfo & info )
{
	return new MockBlendingState( info );
}

}	// sw

