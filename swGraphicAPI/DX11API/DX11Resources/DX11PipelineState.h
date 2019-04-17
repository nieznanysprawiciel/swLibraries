#pragma once
/**
@file PipelineState.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "DX11Initializer/DX11APIObjects.h"

#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"


// ComPtr
#include <wrl/client.h>
using namespace Microsoft::WRL;



namespace sw
{


//====================================================================================//
//				DX11RasterizerState
//====================================================================================//


/**@brief RasterizerState DirectX11.
@ingroup DX11API*/
class DX11RasterizerState : public RasterizerState, protected DX11APIObjects
{
	RTTR_ENABLE( RasterizerState );
private:

	ComPtr< ID3D11RasterizerState >		m_state;
	RasterizerStateInfo					m_info;

protected:

	virtual		~DX11RasterizerState() = default;

public:
	explicit	DX11RasterizerState	( const AssetPath& assetPath, ComPtr< ID3D11RasterizerState > state, const RasterizerStateInfo& info );

	ID3D11RasterizerState*								Get	() { return m_state.Get(); }

	// Inherited via RasterizerState
	virtual const RasterizerStateInfo&					GetDescriptor	() const override;

	static sw::Nullable< DX11RasterizerState* >			Create			(  const AssetPath& assetPath, const RasterizerStateInfo& info );
};

//====================================================================================//
//				DX11DepthStencilState
//====================================================================================//


/**@brief Depth stencil state DirectX11.
@ingroup DX11API*/
class DX11DepthStencilState : public DepthStencilState, public DX11APIObjects
{
	RTTR_ENABLE( DepthStencilState );
private:
	ComPtr< ID3D11DepthStencilState >	m_state;
	DepthStencilInfo					m_info;

protected:
	~DX11DepthStencilState() = default;
public:
	explicit	DX11DepthStencilState	( const AssetPath& assetPath, ComPtr< ID3D11DepthStencilState > state, const DepthStencilInfo& info );

	ID3D11DepthStencilState*							Get	() { return m_state.Get(); }

	// Inherited via DepthStencilState
	virtual const DepthStencilInfo&						GetDescriptor	() const override;

	static sw::Nullable< DX11DepthStencilState* >		Create			( const AssetPath& assetPath, const DepthStencilInfo& info );
};


//====================================================================================//
//				DX11BlendingState
//====================================================================================//


/**@brief Blending state DirectX11.
@ingroup DX11API*/
class DX11BlendingState : public BlendingState, public DX11APIObjects
{
	RTTR_ENABLE( BlendingState );
private:

	ComPtr< ID3D11BlendState >	m_state;
	BlendingInfo				m_info;

protected:

	virtual		~DX11BlendingState	() = default;

public:
	explicit	DX11BlendingState	( const AssetPath& assetPath, ComPtr< ID3D11BlendState > state, const BlendingInfo& info );


	ID3D11BlendState*								Get	() { return m_state.Get(); }

	// Inherited via BlendingState
	virtual const BlendingInfo&						GetDescriptor	() const override;

	static sw::Nullable< DX11BlendingState* >		Create			( const AssetPath& assetPath, const BlendingInfo& info );
};


}	// sw


