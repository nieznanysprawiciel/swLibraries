#pragma once
/**
@file IGraphicAPIInitializer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Deklaracja interfejsu IGraphicAPIInitializer.
*/

#include "swGraphicAPI/Rendering/IRenderer.h"
#include "swGraphicAPI/Resources/SwapChain.h"
#include "swCommonLib/Common/TypesDefinitions.h"

#include <string>



/**@defgroup GraphicAPI
@ingroup ModulesStructure
@brief Interfejsy dla obiekt�w zasob�w, renderera i initializera.

@EngineCore jest niezale�ny od konkretnej implementacji API graficznego, kt�ra
zosta�a u�yta. W tym celu w tym projekcie zgromadzone s� wszystkie interfejsy,
kt�re powinny zosta� zaimplementowane przez dziedzicz�ce API oraz zestawy sta�ych silnikowych
niezale�nych od platformy.

Pliki w tym projekcie powinny zosta� w��czone do ka�dego projektu, kt�ry u�ywa b�d�
implementuje API graficzne. Opr�cz interfejs�w do zaimplementowania, projekt zawiera te�
pliki .cpp, kt�re powinny by� skompilowane do biblioteki statycznej razem z poszczeg�lnymi API graficznymi.*/


/**@brief Przechowuje informacje potrzebne do SwapChaina. Parametr dla funkcji IGraphicAPIInitializer::CreateSwapChain.
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
	SwapChainInitData()
	{
		DefaultSettings();
	}

	void DefaultSettings()
	{
		WindowWidth = 1024;
		WindowHeight = 768;
		FullScreen = false;
		NumBuffers = 1;
		SamplesCount = 1;
		SamplesQuality = 0;
		DepthStencilFormat = DepthStencilFormat::DEPTH_STENCIL_FORMAT_D24_UNORM_S8_UINT;
		BackBufferFormat = ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM;
	}
};

/**@brief Przechowuje informacje potrzebne do inicjalizacji
API graficznego. Parametr dla funkcji IGraphicAPIInitializer::InitAPI.
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

/**@brief Interfejs klasy do inicjowania API graficznego.

Klasa powinna zosta� zainicjowana przez dziedziczace API graficzne.
Podstawowymi funkcjonalno�ciami klasy jest:
- zainicjowanie i zwolnienie API
- stworzenie renderer�w*/
class IGraphicAPIInitializer
{
private:
protected:
public:
	virtual ~IGraphicAPIInitializer() = default;

	virtual IRenderer*		CreateRenderer			( RendererUsage usage )					= 0;
	virtual SwapChain*		CreateSwapChain			( SwapChainInitData& swapChainData )	= 0;
	virtual bool			InitAPI					( GraphicAPIInitData& initData )		= 0;
	virtual void			ReleaseAPI				()										= 0;
	virtual void*			GetRenderTargetHandle	( RenderTargetObject* renderTarget )	= 0;

	// Future
	// virtual std::wstring	GetErrorString() = 0;
};
