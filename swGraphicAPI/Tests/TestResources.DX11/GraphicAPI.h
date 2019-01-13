#pragma once

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"



// ================================ //
//
struct Graphic
{
	IGraphicAPIInitializer*		API;
	ResourceManager*			RM;

// ================================ //
//
	~Graphic()
	{
		if( API ) delete API;
		if( RM ) delete RM;

		API = nullptr;
		RM = nullptr;
	}
};


// ================================ //
//
inline Graphic&			GetGraphic	()
{
	static Graphic graphic;

	if( !graphic.API )
	{
		graphic.API = ResourcesFactory::CreateAPIInitializer();

		GraphicAPIInitData graphicApiData;
		graphicApiData.CreateSwapChain = false;		// We will create swap chain and render target later with window.
		graphicApiData.SingleThreaded = true;
		graphicApiData.UseDebugLayer = false;

		auto result = graphic.API->InitAPI( graphicApiData );
	}

	if( !graphic.RM )
	{
		graphic.RM = new ResourceManager();
	}

	return graphic;
}

