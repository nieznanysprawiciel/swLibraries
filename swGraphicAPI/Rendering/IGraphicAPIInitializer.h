#pragma once
/**
@file IGraphicAPIInitializer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Rendering/IRenderer.h"
#include "swGraphicAPI/Resources/SwapChain.h"

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include <string>



namespace sw
{


/**@defgroup GraphicAPI
@ingroup ModulesStructure
@brief Interfaces for Resources, rendering and resources management.
*/


/**@brief Stores information for SwapChain initialization. Parameter for function IGraphicAPIInitializer::CreateSwapChain.
@ingroup GraphicAPI*/
struct SwapChainInitData
{
	uint16			WindowWidth;
	uint16			WindowHeight;
	WindowHandler	WindowHandle;
	bool			FullScreen;
	uint8			SamplesCount;
	uint8			SamplesQuality;
	uint8			NumBuffers;
	DepthStencilFormat		DepthStencilFormat;
	ResourceFormat			BackBufferFormat;

// ================================ //
//
	explicit SwapChainInitData()
	{
		DefaultSettings();
	}

	void DefaultSettings()
	{
		WindowWidth = 1024;
		WindowHeight = 768;
		WindowHandle = nullptr;
		FullScreen = false;
		NumBuffers = 1;
		SamplesCount = 1;
		SamplesQuality = 0;
		DepthStencilFormat = DepthStencilFormat::DEPTH_STENCIL_FORMAT_D24_UNORM_S8_UINT;
		BackBufferFormat = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
	}
};

/**@brief GraphicAPI initialialization data. Parameter for function IGraphicAPIInitializer::InitAPI.
@ingroup GraphicAPI*/
struct GraphicAPIInitData
{
	SwapChainInitData	SwapChain;
	bool				SingleThreaded;
	bool				UseDebugLayer;
	bool				CreateSwapChain;	// You can create SwapChain and main render target later.

// ================================ //
//
	GraphicAPIInitData()
	{
		DefaultSettings();
	}

	void DefaultSettings()
	{
		SingleThreaded = true;
		UseDebugLayer = false;
		CreateSwapChain = true;
	}
};

/**@brief Graphic API interface.

@todo Use Nullable in functions that can fail.
@ingroup GraphicAPI*/
class IGraphicAPIInitializer
{
private:
protected:
public:
	virtual ~IGraphicAPIInitializer() = default;

	virtual IRenderer*		CreateRenderer			( RendererUsage usage ) = 0;
	virtual SwapChain*		CreateSwapChain			( const SwapChainInitData& swapChainData ) = 0;
	virtual ReturnResult	InitAPI					( const GraphicAPIInitData& initData ) = 0;
	virtual void			ReleaseAPI				() = 0;
	virtual void*			GetRenderTargetHandle	( RenderTarget* renderTarget ) = 0;
};

}	// sw


