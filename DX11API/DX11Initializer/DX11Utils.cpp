/**
@file DX11Utils.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11Utils.h"
#include "DX11Utils.inl"

#include "DX11ConstantsMapper.h"
//#include <DXGI.h>



// ================================ //
//
DXGI_SWAP_CHAIN_DESC			DX11Utils::CreateSwapChainDesc		( const SwapChainInitData& swapChainData )
{
	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferCount = swapChainData.NumBuffers;
	desc.BufferDesc.Format = DX11ConstantsMapper::Get( swapChainData.BackBufferFormat );
	desc.BufferDesc.Height = swapChainData.WindowHeight;
	desc.BufferDesc.Width = swapChainData.WindowWidth;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = (HWND)swapChainData.WindowHandle;
	desc.SampleDesc.Count = swapChainData.SamplesCount;
	desc.SampleDesc.Quality = swapChainData.SamplesQuality;
	desc.Windowed = swapChainData.WindowHandle != 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	return desc;
}

// ================================ //
//
DXGI_SWAP_CHAIN_DESC1			DX11Utils::CreateSwapChainDesc1		( const SwapChainInitData& swapChainData )
{
	DXGI_SWAP_CHAIN_DESC1 desc;
	desc.BufferCount = swapChainData.NumBuffers;
	desc.Format = DX11ConstantsMapper::Get( swapChainData.BackBufferFormat );
	desc.Height = swapChainData.WindowHeight;
	desc.Width = swapChainData.WindowWidth;
	desc.SampleDesc.Count = swapChainData.SamplesCount;
	desc.SampleDesc.Quality = swapChainData.SamplesQuality;
	desc.Stereo = false;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.Scaling = DXGI_SCALING_STRETCH;
    desc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	desc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
    desc.Flags = 0;

	return desc;
}

// ================================ //
//
ComPtr< IDXGIAdapter >			DX11Utils::GetDXGIAdapter			()
{
	HRESULT result;

	ComPtr< IDXGIDevice > dxgiDevice = nullptr;
	result = device->QueryInterface( __uuidof( IDXGIDevice ), (void**)&dxgiDevice );
	
	assert( SUCCEEDED( result ) );
	if( FAILED( result ) )	return nullptr;

	ComPtr< IDXGIAdapter > dxgiAdapter = nullptr;
	result = dxgiDevice->GetParent( __uuidof( IDXGIAdapter ), (void **)&dxgiAdapter );
	
	assert( SUCCEEDED( result ) );
	if( FAILED( result ) )	return nullptr;

	return dxgiAdapter;
}

// ================================ //
//
ComPtr< IDXGISwapChain >		DX11Utils::CreateWindowSwapChain		( const SwapChainInitData & swapChainData )
{
	DXGI_SWAP_CHAIN_DESC desc = DX11Utils::CreateSwapChainDesc( swapChainData );

	ComPtr< IDXGIFactory > dxgiFactory = DX11Utils::GetDXGIFactory();
	if( !dxgiFactory )
		return nullptr;

// Swap chain
	ComPtr< IDXGISwapChain > swapChain;
	HRESULT result = dxgiFactory->CreateSwapChain( device, &desc, &swapChain );
	assert( SUCCEEDED( result ) );

	return swapChain;
}

// ================================ //
//
ComPtr< IDXGISwapChain >		DX11Utils::CreateCompositionSwapChain	( const SwapChainInitData & swapChainData )
{
	DXGI_SWAP_CHAIN_DESC1 desc = DX11Utils::CreateSwapChainDesc1( swapChainData );

	ComPtr< IDXGIFactory2 > dxgiFactory = DX11Utils::GetDXGIFactory2();
	if( !dxgiFactory )
		return nullptr;

// Swap chain
	ComPtr< IDXGISwapChain1 > swapChain;
	HRESULT result = dxgiFactory->CreateSwapChainForComposition( device, &desc, nullptr, swapChain.GetAddressOf() );
	assert( SUCCEEDED( result ) );

	return swapChain;
}

// ================================ //
//
ComPtr< IDXGIFactory >			DX11Utils::GetDXGIFactory			()
{
	return GetFactory< IDXGIFactory >();
}

// ================================ //
//
ComPtr< IDXGIFactory2 >			DX11Utils::GetDXGIFactory2			()
{
	return GetFactory< IDXGIFactory2 >();
}

