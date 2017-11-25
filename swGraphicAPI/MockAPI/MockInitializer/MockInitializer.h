#pragma once
/**
@file MockInitializer.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.
*/

#include "swCommonLib/Common/Nullable.h"

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
	virtual SwapChain*		CreateSwapChain			( SwapChainInitData& swapChainData ) override;
	virtual bool			InitAPI					( GraphicAPIInitData& initData ) override;
	virtual void			ReleaseAPI				() override;
	virtual void*			GetRenderTargetHandle	( RenderTargetObject* renderTarget ) override;

private:
	Nullable< bool >		InitDevices				( GraphicAPIInitData& initData );
};

}	// sw
