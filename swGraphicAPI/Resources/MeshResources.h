#pragma once
/**
@file MeshResources.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.

@brief This file contains includes for low level API dependent Resources.
*/



#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Resources/Shaders/IShader.h"
#include "swGraphicAPI/Resources/Buffers/Buffer.h"
#include "swGraphicAPI/Resources/Textures/RenderTarget.h"
#include "swGraphicAPI/Resources/Shaders/IShaderInputLayout.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"


#include "swGraphicAPI/Resources/Shaders/Shaders.h"
#include "swGraphicAPI/Resources/Shaders/InputLayout.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"

#include "swGraphicAPI/Resources/Textures/Texture.h"

#include "swGraphicAPI/Resources/PipelineStates/BlendingState.h"
#include "swGraphicAPI/Resources/PipelineStates/DepthStencilState.h"
#include "swGraphicAPI/Resources/PipelineStates/RasterizerState.h"

#include <DirectXMath.h>


//definicje
/** @def WRONG_ID
B³êdny identyfikator assetu w klasie @ref Resource.*/
#define WRONG_ID						0

/**@defgroup Resources Resources
@ingroup ResourcesManagment
@ingroup GraphicAPI
@brief Low level resources that depend on graphic API.

Zasoby s¹ silnie zale¿ne od u¿ywanej platformy sprzêtowej. W celu oddzielenia referencji do
API graficznego od @ref EngineCore, wszystkie obiekty silnika u¿ywaj¹ jedynie klas bazowych, które
s¹ implementowane przez poszczególne API graficzne. Aby zobaczyæ konkretne implementacje tych klas
zobacz @ref GraphicAPI.

Zasoby nigdy nie s¹ tworzone bezpoœrednio. Zamiast tego u¿ywa siê klasy @ref ResourcesFactory, któr¹
implementuje konkretne API graficzne.

Poniewa¿ zasoby mog¹ byæ wspó³dzielone przez wiele obiektów w silniku, istnieje mechanizm zliczania
odwo³añ do obiektów implementowany przez klasê @ref Resource.*/



namespace sw
{




typedef uint16 Index16;
typedef uint32 Index32;
typedef uint8 Index8;


/**@brief Meaning of texture indicies.

@ingroup Textures

@deprecated I don't think it's good way to handle textures semantic.

These are values used by default shaders. You don't have to use this convention
when you write your own shaders.*/
enum TextureUse
{
	TEX_DIFFUSE			///<Tekstura dla kana³u diffuse
	, TEX_SPECULAR		///<Tekstura dla kana³u specular
	, TEX_EMISSIVE		///< Texture for emmisive channel
	, TEX_BUMP_MAP		///<Bump mapa
	, TEX_DISPLACEMENT_MAP		///<Tekstura przemieszczeñ wierzcho³ków, w przypadku u¿ywania teselacji wierzcho³ków
	, TEX_OTHER1		///<Tekstura o dowolnym znaczeniu
	, TEX_OTHER2		///<Tekstura o dowolnym znaczeniu
	, TEX_LIGHTMAP		///<Lightmapa
};


}	// sw

