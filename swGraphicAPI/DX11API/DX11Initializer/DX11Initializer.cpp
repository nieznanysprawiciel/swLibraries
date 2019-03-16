/**
@file DX11Initializer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/DX11API/stdafx.h"


#include "DX11Initializer.h"
#include "DX11Renderer/DX11Renderer.h"
#include "DX11Resources/DX11RenderTarget.h"
#include "DX11Resources/DX11Texture.h"
#include "DX11Resources/DX11SwapChain.h"
#include "DX11ConstantsMapper.h"

#include "DX11Utils.h"

//#include <comdef.h>

// ComPtr
#include <wrl/client.h>
using namespace Microsoft::WRL;



namespace sw
{



// ================================ //
//
DX11Initializer::DX11Initializer()
{
	m_rasterizer = nullptr;
	m_depthState = nullptr;
}

/**@brief Creates renderer.

@param[in] usage Specyfikuje czy u�y� op�nionego kontekstu renderowania czy natychmiastowego.
@note Wszystkie renderery stworzone w aplikacji powinny by� tego samego typu.*/
IRenderer*			DX11Initializer::CreateRenderer			( RendererUsage usage )
{
	return new DX11Renderer( usage );
}

/**@brief Creates new SwapChain.*/
SwapChain*			DX11Initializer::CreateSwapChain		( const SwapChainInitData& swapChainData )
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC desc = DX11Utils::CreateSwapChainDesc( swapChainData );

	ComPtr< IDXGIFactory > dxgiFactory = DX11Utils::GetDXGIFactory();
	if( !dxgiFactory )
		return nullptr;

// Swap chain
	ComPtr< IDXGISwapChain > swapChain;
	if( swapChainData.WindowHandle )
		swapChain = DX11Utils::CreateWindowSwapChain( swapChainData );
	else
		swapChain = DX11Utils::CreateCompositionSwapChain( swapChainData );

	if( !swapChain )
		return nullptr;

// Render target
	ComPtr< ID3D11Texture2D > backBuffer = nullptr;
	result = swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (LPVOID*)backBuffer.GetAddressOf() );
	if( FAILED( result ) )	return nullptr;

	ComPtr< ID3D11RenderTargetView > renderTargetView;
	result = device->CreateRenderTargetView( backBuffer.Get(), nullptr, renderTargetView.GetAddressOf() );
	if( FAILED( result ) )	return nullptr;

// Depth buffer
	_z_buffer_desc.Format = DX11ConstantsMapper::Get( swapChainData.DepthStencilFormat );
	_z_buffer_desc.Width = swapChainData.WindowWidth;
	_z_buffer_desc.Height = swapChainData.WindowHeight;
	_z_buffer_desc.MipLevels = 1;
	_z_buffer_desc.ArraySize = 1;
	_z_buffer_desc.SampleDesc.Count = swapChainData.SamplesCount;
	_z_buffer_desc.SampleDesc.Quality = swapChainData.SamplesQuality;
	_z_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	_z_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	_z_buffer_desc.CPUAccessFlags = 0;
	_z_buffer_desc.MiscFlags = 0;

	_z_buffer_view_desc.Format = _z_buffer_desc.Format;


	ComPtr< ID3D11Texture2D > backBufferDepth = nullptr;
	result = device->CreateTexture2D( &_z_buffer_desc, nullptr, backBufferDepth.GetAddressOf() );
	if( FAILED( result ) )	return nullptr;

	ComPtr< ID3D11DepthStencilView > zBufferView;
	result = device->CreateDepthStencilView( backBufferDepth.Get(), &_z_buffer_view_desc, zBufferView.GetAddressOf() );
	if( FAILED( result ) )	return nullptr;


	DX11RenderTarget* renderTargetObject = new DX11RenderTarget( renderTargetView, zBufferView, nullptr, nullptr, nullptr );
	renderTargetObject->SetHeight( static_cast<uint16>( swapChainData.WindowHeight ) );
	renderTargetObject->SetWidth( static_cast<uint16>( swapChainData.WindowWidth ) );

	DX11SwapChain* newSwapChain = new DX11SwapChain( swapChain.Detach(), renderTargetObject );
	return newSwapChain;
}

// ================================ //
//
SwapChain*			DX11Initializer::CreateWindowSwapChain		( const SwapChainInitData& swapChainData )
{
	return nullptr;
}

// ================================ //
//
SwapChain*			DX11Initializer::CreateCompositionSwapChain	( const SwapChainInitData& swapChainData )
{
	return nullptr;
}

/**@brief Initializes graphic API.

@param[in] initData Dane u�ywane do inicjalizacji.
@return Zwraca true, je�eli inicjalizacja si� uda.*/
ReturnResult			DX11Initializer::InitAPI		( const GraphicAPIInitData& initData )
{
	set_depth_stencil_format( DX11ConstantsMapper::Get( initData.SwapChain.DepthStencilFormat ) );

	m_useDebugLayer = initData.UseDebugLayer;

	DX11_INIT_RESULT result;
	if( initData.CreateSwapChain )
	{
		result = init_DX11( initData.SwapChain.WindowWidth,
							initData.SwapChain.WindowHeight,
							(HWND)initData.SwapChain.WindowHandle,
							initData.SwapChain.FullScreen,
							initData.SingleThreaded );

		if( result != DX11_INIT_RESULT::DX11_INIT_OK )
			return "Failed to init DirectX 11";			///< @todo More descriptive error message.
	}
	else
	{
		auto result = InitDevices( initData );
		if( !result.IsValid() )
			return result;
	}

	result = init_sampler();
	if( result != DX11_INIT_OK )
	{
		release_DirectX();	// Jak tu co� si� nie uda�o, to znaczy, �e deskryptor by� niepoprawny.
		return "Failed to create sampler.";
	}

	if( FAILED( device->CreateRasterizerState( &get_rasterizer_desc(), &m_rasterizer ) ) )
		return "Failed to create RasterizerState.";

	device_context->RSSetState( m_rasterizer );

	//D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	//depthStencilDesc.DepthEnable = true;
	//depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	//depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	//depthStencilDesc.StencilEnable = false;
	//depthStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	//depthStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	//depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	//depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	//depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//if( FAILED( device->CreateDepthStencilState( &depthStencilDesc, &m_depthState ) ) )
	//	return false;

	//device_context->OMSetDepthStencilState( m_depthState, 0 );

	return Result::Success;
}

/**@brief Zwalnia stworzone obiekty DirectX 11.*/
void				DX11Initializer::ReleaseAPI()
{
	if( m_rasterizer )
		m_rasterizer->Release();
	m_rasterizer = nullptr;

	if( m_depthState )
		m_depthState->Release();
	m_depthState = nullptr;

	release_DirectX();
}

/**@brief Zwraca wska�nik na bufor koloru render targetu.

Ta funkcja jest u�ywana do wsp�pracy z zewn�trznymi aplikacjami, kt�re potrzebuj� bezpo�redniego
wska�nika na zasoby DirectXowe. Nie ma �adnego powodu, �eby jej u�ywa� w innych przypadkach.

@param[in] renderTarget RenderTarget, z kt�rego ma zosta� wzi�tu wska�nik.
@return Zwraca wska�nik na widok na bufor koloru render targetu lub nullptr,
jezeli podano niepoprawny render target.*/
void*				DX11Initializer::GetRenderTargetHandle( RenderTarget* renderTarget )
{
	DX11RenderTarget* renderTargetDX11 = static_cast<DX11RenderTarget*>( renderTarget );

	if( renderTargetDX11 )
	{
		auto colorBufferTex = static_cast<DX11Texture*>( renderTargetDX11->GetColorBuffer() );
		if( colorBufferTex )
		{
			ComPtr< ID3D11Resource > renderTargetTexture;
			auto colorBufferView = colorBufferTex->Get();
			colorBufferView->GetResource( &renderTargetTexture );

			return renderTargetTexture.Get();
		}
	}
	return nullptr;
}

/**@brief Creates only device and device context.*/
ReturnResult		DX11Initializer::InitDevices	( const GraphicAPIInitData& initData )
{
	UINT createDeviceFlags = 0;


	if( initData.UseDebugLayer )
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	if( initData.SingleThreaded )
		// Domy�lnie obiekt ID3D11Device jest synchronizowany, ale mo�na to wy��czy�
		createDeviceFlags |= D3D11_CREATE_DEVICE_SINGLETHREADED;

	auto result = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, _feature_levels, _num_feature_levels, D3D11_SDK_VERSION, &device, &_current_feature_level, &device_context );
	if( FAILED( result ) )
		return "Creating device failed. Error: " + DX11Utils::ErrorString( result );


	if( initData.UseDebugLayer )
	{
		result = device->QueryInterface( __uuidof( ID3D11Debug ), (void**)&debug_interface );
		if( FAILED( result ) )
			return "Creating debug layer failed";
	}

	return Result::Success;
}


}	// sw
