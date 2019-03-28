#pragma once

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/Resources/ResourcesFactory.h"
#include "swGraphicAPI/Rendering/IGraphicAPIInitializer.h"



// ================================ //
//
struct Graphic
{
	sw::IGraphicAPIInitializer*		API;
	ResourceManager*				RM;

// ================================ //
//
	~Graphic()
	{
		if( RM ) delete RM;
		if( API )
		{
			API->ReleaseAPI();
			delete API;
		}

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
		graphic.API = sw::ResourcesFactory::CreateAPIInitializer();

		sw::GraphicAPIInitData graphicApiData;
		graphicApiData.CreateSwapChain = false;		// We will create swap chain and render target later with window.
		graphicApiData.SingleThreaded = true;
		graphicApiData.UseDebugLayer = true;

		auto result = graphic.API->InitAPI( graphicApiData );
	}

	if( !graphic.RM )
	{
		graphic.RM = new ResourceManager();
	}

	return graphic;
}

