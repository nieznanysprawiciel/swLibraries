#pragma once
/**
@file MockInitializer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"
#include "swGraphicAPI/Resources/SwapChain.h"


/**@defgroup MockAPI
@brief Mock implementation of graphic API objects for testing and debugging.
@ingroup GraphicAPI
*/



namespace sw
{


/**@brief
@ingroup MockAPI*/
class MockInitializer : public IGraphicAPIInitializer
{
private:
protected:
public:
	MockInitializer();
	~MockInitializer() = default;

	virtual IRenderer*		CreateRenderer			( RendererUsage usage ) override;
	virtual SwapChain*		CreateSwapChain			( const SwapChainInitData& swapChainData ) override;
	virtual ReturnResult	InitAPI					( const GraphicAPIInitData& initData ) override;
	virtual void			ReleaseAPI				() override;
	virtual void*			GetRenderTargetHandle	( RenderTarget* renderTarget ) override;

private:
	ReturnResult			InitDevices				( const GraphicAPIInitData& initData );
};

}	// sw
