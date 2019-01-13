/**
@file DX11Initializaer.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "MockInitializer.h"
#include "MockRenderer/MockRenderer.h"
#include "MockResources/MockRenderTarget.h"
#include "MockResources/MockTexture.h"
#include "MockResources/MockSwapChain.h"




namespace sw
{


// ================================ //
//
MockInitializer::MockInitializer()
{}

/**@brief */
IRenderer*			MockInitializer::CreateRenderer		( RendererUsage usage )
{
	return new MockRenderer( usage );
}

/**@brief */
SwapChain*			MockInitializer::CreateSwapChain	( const SwapChainInitData& swapChainData )
{
	MockRenderTarget* renderTargetObject = new MockRenderTarget( nullptr, nullptr, nullptr );
	renderTargetObject->SetHeight( static_cast<uint16>( swapChainData.WindowHeight ) );
	renderTargetObject->SetWidth( static_cast<uint16>( swapChainData.WindowWidth ) );

	MockSwapChain* newSwapChain = new MockSwapChain( renderTargetObject );
	return newSwapChain;
}

/**@brief */
bool				MockInitializer::InitAPI			( const GraphicAPIInitData& initData )
{
	return true;
}

/**@brief */
void				MockInitializer::ReleaseAPI			()
{}

/**@brief Not working. Use regular API.*/
void*				MockInitializer::GetRenderTargetHandle	( RenderTargetObject* renderTarget )
{
	return nullptr;
}

/**@brief Creates only device and device context.*/
Nullable< bool >	MockInitializer::InitDevices		( const GraphicAPIInitData& initData )
{
	return true;
}

}	// sw


