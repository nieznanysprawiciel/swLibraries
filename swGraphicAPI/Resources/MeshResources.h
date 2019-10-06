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
B��dny identyfikator assetu w klasie @ref Resource.*/
#define WRONG_ID						0

/**@defgroup Resources Resources
@ingroup ResourcesManagment
@ingroup GraphicAPI
@brief Low level resources that depend on graphic API.

Zasoby s� silnie zale�ne od u�ywanej platformy sprz�towej. W celu oddzielenia referencji do
API graficznego od @ref EngineCore, wszystkie obiekty silnika u�ywaj� jedynie klas bazowych, kt�re
s� implementowane przez poszczeg�lne API graficzne. Aby zobaczy� konkretne implementacje tych klas
zobacz @ref GraphicAPI.

Zasoby nigdy nie s� tworzone bezpo�rednio. Zamiast tego u�ywa si� klasy @ref ResourcesFactory, kt�r�
implementuje konkretne API graficzne.

Poniewa� zasoby mog� by� wsp�dzielone przez wiele obiekt�w w silniku, istnieje mechanizm zliczania
odwo�a� do obiekt�w implementowany przez klas� @ref Resource.*/



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
	TEX_DIFFUSE			///<Tekstura dla kana�u diffuse
	, TEX_SPECULAR		///<Tekstura dla kana�u specular
	, TEX_EMISSIVE		///< Texture for emmisive channel
	, TEX_BUMP_MAP		///<Bump mapa
	, TEX_DISPLACEMENT_MAP		///<Tekstura przemieszcze� wierzcho�k�w, w przypadku u�ywania teselacji wierzcho�k�w
	, TEX_OTHER1		///<Tekstura o dowolnym znaczeniu
	, TEX_OTHER2		///<Tekstura o dowolnym znaczeniu
	, TEX_LIGHTMAP		///<Lightmapa
};


}	// sw

