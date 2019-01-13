#pragma once

#include "DX11APIObjects.h"
#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"

#include <d3d11_1.h>


/**@brief Helper functions for DirecX objects managment.*/
class DX11Utils : protected DX11APIObjects
{
private:
protected:
public:
	explicit		DX11Utils		() = default;
	~DX11Utils	() = default;


public:

	static DXGI_SWAP_CHAIN_DESC			CreateSwapChainDesc		( const SwapChainInitData& swapChainData);
	static DXGI_SWAP_CHAIN_DESC1		CreateSwapChainDesc1	( const SwapChainInitData& swapChainData);

public:

	static ComPtr< IDXGIFactory >				GetDXGIFactory			();
	static ComPtr< IDXGIFactory2 >				GetDXGIFactory2			();
	static ComPtr< IDXGIAdapter >				GetDXGIAdapter			();

	static ComPtr< IDXGISwapChain >			CreateWindowSwapChain		( const SwapChainInitData& swapChainData );
	static ComPtr< IDXGISwapChain >			CreateCompositionSwapChain	( const SwapChainInitData& swapChainData );

private:

	template< typename FactoryType >
	static ComPtr< FactoryType >				GetFactory				();
};



