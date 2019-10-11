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

MockRasterizerState::MockRasterizerState	( const AssetPath& name, const RasterizerStateInfo& info )
	:	RasterizerState( name )
	,	m_info( info )
{}

// ================================ //
//
const RasterizerStateInfo&		MockRasterizerState::GetDescriptor	() const
{
	return m_info;
}

// ================================ //
//
MockRasterizerState*			MockRasterizerState::Create		( const AssetPath& name, const RasterizerStateInfo& info )
{
	return new MockRasterizerState( name, info );
}



//====================================================================================//
//			DepthStencilState	
//====================================================================================//

MockDepthStencilState::MockDepthStencilState	( const AssetPath& name, const DepthStencilInfo& info )
	:	DepthStencilState( name )
	,	m_info( info )
{}

// ================================ //
//
const DepthStencilInfo&			MockDepthStencilState::GetDescriptor	() const
{
	return m_info;
}

// ================================ //
//
MockDepthStencilState*			MockDepthStencilState::Create			( const AssetPath& name, const DepthStencilInfo& info )
{
	return new MockDepthStencilState( name, info );
}



//====================================================================================//
//			BlendingState	
//====================================================================================//

MockBlendingState::MockBlendingState	( const AssetPath& name, const BlendingInfo& info )
	:	BlendingState( name )
	,	m_info( info )
{}


// ================================ //
//
const BlendingInfo&				MockBlendingState::GetDescriptor	() const
{
	return m_info;
}

// ================================ //
//
MockBlendingState*				MockBlendingState::Create		( const AssetPath& name, const BlendingInfo & info )
{
	return new MockBlendingState( name, info );
}

}	// sw

