#pragma once
/**
@file DX11Initializer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"
#include "DX11APIObjects.h"
#include "swGraphicAPI/Resources/SwapChain.h"



namespace sw
{


/**@defgroup DX11API
@brief Implements renderer, initializer and resource objects in DirectX 11.
@ingroup GraphicAPI
*/


/**@brief Class implements IGraphicAPIInitializer in DirectX 11.
@ingroup DX11API

Jako klasa pomocnicza do inicjalizacji jest u¿ywana klasa @ref DX11AuxiliaryObjects
(inherits @ref DX11APIObjects).
*/
class DX11Initializer : public IGraphicAPIInitializer, public DX11AuxiliaryObjects
{
private:
	ID3D11RasterizerState*		m_rasterizer;
	ID3D11DepthStencilState*	m_depthState;
protected:
public:
	DX11Initializer();
	~DX11Initializer() = default;

	virtual IRenderer*		CreateRenderer			( RendererUsage usage ) override;
	virtual SwapChain*		CreateSwapChain			( const SwapChainInitData& swapChainData ) override;
	virtual ReturnResult	InitAPI					( const GraphicAPIInitData& initData ) override;
	virtual void			ReleaseAPI				() override;
	virtual void*			GetRenderTargetHandle	( RenderTargetObject* renderTarget ) override;

private:

	ReturnResult			InitDevices				( const GraphicAPIInitData& initData );

	SwapChain*				CreateWindowSwapChain		( const SwapChainInitData& swapChainData );
	SwapChain*				CreateCompositionSwapChain	( const SwapChainInitData& swapChainData );
};


}	// sw

