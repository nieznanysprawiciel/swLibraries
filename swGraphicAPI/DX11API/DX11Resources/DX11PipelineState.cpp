/**
@file DX11PipelineState.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11PipelineState.h"
#include "DX11Initializer/DX11ConstantsMapper.h"
#include "swGraphicAPI/DX11API/DX11Initializer/DX11Utils.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11RasterizerState >( "sw::DX11RasterizerState" );
	rttr::registration::class_< sw::DX11DepthStencilState >( "sw::DX11DepthStencilState" );
	rttr::registration::class_< sw::DX11BlendingState >( "sw::DX11BlendingState" );
}


namespace sw
{



//====================================================================================//
//			RasterizerState	
//====================================================================================//

DX11RasterizerState::DX11RasterizerState		( const AssetPath& assetPath, ComPtr< ID3D11RasterizerState > state, const RasterizerStateInfo& info )
	: RasterizerState( assetPath )
	, m_state( state )
	, m_info( info )
{}


// ================================ //
//
const RasterizerStateInfo&						DX11RasterizerState::GetDescriptor		() const
{
	return m_info;
}

// ================================ //
//
sw::Nullable< DX11RasterizerState* >			DX11RasterizerState::Create				( const AssetPath& assetPath, const RasterizerStateInfo& info )
{
	D3D11_RASTERIZER_DESC desc;
	desc.CullMode = DX11ConstantsMapper::Get( info.CullMode );
	desc.FillMode = DX11ConstantsMapper::Get( info.FillMode );
	desc.DepthBias = info.DepthBias;
	desc.FrontCounterClockwise = info.IsClockwise ? FALSE : TRUE;
	desc.ScissorEnable = info.EnableScissor;
	desc.DepthClipEnable = info.EnableZClipping;
	desc.SlopeScaledDepthBias = 0.0f;
	desc.DepthBiasClamp = 0.0f;
	desc.MultisampleEnable = false;
	desc.AntialiasedLineEnable = false;

	ComPtr< ID3D11RasterizerState > state;
	auto result = device->CreateRasterizerState( &desc, state.GetAddressOf() );
	if( FAILED( result ) )
		return fmt::format( "[DX11RasterizerState] Creation failed.", DX11Utils::ErrorString( result ) );

	return new DX11RasterizerState( assetPath, state, info );
}



//====================================================================================//
//			DepthStencilState	
//====================================================================================//

DX11DepthStencilState::DX11DepthStencilState	( const AssetPath& assetPath, ComPtr< ID3D11DepthStencilState > state, const DepthStencilInfo& info )
	: DepthStencilState( assetPath )
	, m_state( state )
	, m_info( info )
{}

// ================================ //
//
const DepthStencilInfo&							DX11DepthStencilState::GetDescriptor	() const
{
	return m_info;
}

// ================================ //
//
sw::Nullable< DX11DepthStencilState* >			DX11DepthStencilState::Create			( const AssetPath& assetPath, const DepthStencilInfo& info )
{
	D3D11_DEPTH_STENCIL_DESC desc;
	desc.DepthEnable = info.EnableDepthTest;
	desc.StencilEnable = info.EnableStencilTest;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;

	ComPtr< ID3D11DepthStencilState > state;
	auto result = device->CreateDepthStencilState( &desc, state.GetAddressOf() );
	if( FAILED( result ) )
        return fmt::format( "[DX11DepthStencilState] Creation failed.", DX11Utils::ErrorString( result ) );

	return new DX11DepthStencilState( assetPath, state, info );
}



//====================================================================================//
//			BlendingState	
//====================================================================================//

DX11BlendingState::DX11BlendingState	( const AssetPath& assetPath, ComPtr< ID3D11BlendState > state, const BlendingInfo& info )
	: BlendingState( assetPath )
	, m_state( state )
	, m_info( info )
{}

// ================================ //
//
const BlendingInfo&						DX11BlendingState::GetDescriptor	() const
{
	return m_info;
}

// ================================ //
//
sw::Nullable< DX11BlendingState* >		DX11BlendingState::Create			( const AssetPath& assetPath, const BlendingInfo& info )
{
	D3D11_BLEND_DESC desc;
	desc.IndependentBlendEnable = false;
	desc.AlphaToCoverageEnable = false;
	desc.RenderTarget[ 0 ].BlendEnable = info.EnableBlending;
	desc.RenderTarget[ 0 ].BlendOp = DX11ConstantsMapper::Get( info.ColorOperation );
	desc.RenderTarget[ 0 ].BlendOpAlpha = DX11ConstantsMapper::Get( info.AlphaOperation );

	desc.RenderTarget[ 0 ].SrcBlend = DX11ConstantsMapper::Get( info.SrcColorBlend );
	desc.RenderTarget[ 0 ].DestBlend = DX11ConstantsMapper::Get( info.DstColorBlend );

	desc.RenderTarget[ 0 ].SrcBlendAlpha = DX11ConstantsMapper::Get( info.SrcAlphaBlend );
	desc.RenderTarget[ 0 ].DestBlendAlpha = DX11ConstantsMapper::Get( info.DstAlphaBlend );
	desc.RenderTarget[ 0 ].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ComPtr< ID3D11BlendState > state;
	auto result = device->CreateBlendState( &desc, state.GetAddressOf() );
	if( FAILED( result ) )
        return fmt::format( "[DX11BlendingState] Creation failed.", DX11Utils::ErrorString( result ) );

	return new DX11BlendingState( assetPath, state, info );
}

}	// sw


