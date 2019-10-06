#pragma once
/**
@file GraphicAPI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/Loaders/ShaderLoader.h"
#include "swGraphicAPI/ResourceManager/Loaders/RenderTargetLoader.h"
#include "swGraphicAPI/Loaders/SoilTextureLoader/SoilTextureLoader.h"

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


namespace sw
{

// ================================ //
//
inline std::unique_ptr< ResourceManager >			CreateResourceManagerWithDefaults		()
{
	std::unique_ptr< ResourceManager > rm = std::make_unique< ResourceManager >();

	{
		auto loader = std::make_shared< ShaderLoader >();
		rm->RegisterLoader( loader );
	}

	{
		auto loader = std::make_shared< RenderTargetLoader >();
		rm->RegisterLoader( loader );
	}

	return std::move( rm );
}


// ================================ //
//
inline std::unique_ptr< ResourceManager >			CreateRMWithDefaultsSoil				()
{
	auto rm = CreateResourceManagerWithDefaults();

	{
		auto loader = std::make_shared< SoilTextureLoader >();
		rm->RegisterLoader( loader );
	}

	return std::move( rm );
}


}	// sw

