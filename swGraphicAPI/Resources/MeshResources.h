#pragma once
/**
@file MeshResources.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Plik zawiera deklaracje format�w wierzcho�k�w oraz klas zawieraj�cych assety shadery itp.
*/


#include "swCommonLib/Common/ObjectDeleter.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Resources/IShader.h"
#include "swGraphicAPI/Resources/IBuffer.h"
#include "swGraphicAPI/Resources/IRenderTarget.h"
#include "swGraphicAPI/Resources/IShaderInputLayout.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"
#include "swGraphicAPI/Resources/BufferInitData.h"

#include "swGraphicAPI/Resources/Shaders/Shaders.h"
#include "swGraphicAPI/Resources/Shaders/InputLayout.h"
#include "swGraphicAPI/Resources/Shaders/LayoutInitData.h"

#include "swGraphicAPI/Resources/Textures/Texture.h"

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


class BufferObject;
class TextureObject;
class VertexShader;
class PixelShader;


/*
// W buforze wierzcho�k�w znajduj� si� elementy typu VERT_INDEX.
// Definicja typu VERT_INDEX znajduje si� w pliku macros_switches.h i wygl�da tak:

#if defined(INDEX_BUFFER_UINT16)
typedef UINT16 VERT_INDEX;
#elif defined(INDEX_BUFFER_UINT32)
typedef UINT32 VERT_INDEX;
#else
typedef UINT32 VERT_INDEX;
#endif

*/


static const std::wstring RENDER_TARGET_COLOR_BUFFER_NAME = L"::color";
static const std::wstring RENDER_TARGET_DEPTH_BUFFER_NAME = L"::depth";
static const std::wstring RENDER_TARGET_STENCIL_BUFFER_NAME = L"::stencil";


typedef uint16 Index16;
typedef uint32 Index32;
typedef uint8 Index8;


/**@brief Meaning of texture indicies.

@ingroup Textures

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



//----------------------------------------------------------------------------------------------//
//								RenderTargetObject												//
//----------------------------------------------------------------------------------------------//

/**@defgroup RenderTargets RenderTargets
@ingroup Resources
*/

/**@brief Struktura u�ywana do tworzenia render targetu.
@ingroup RenderTargets*/
struct RenderTargetDescriptor
{
	uint16				TextureWidth;				///<Szeroko�� tekstury w pikselach.
	uint16				TextureHeight;				///<Wysoko�� tekstury w pikselach.
	uint16				ArraySize;					///<Liczba element�w tablicy.
	bool				CPURead : 1;				///<Pozwala na odczyt tekstury przez CPU.
	bool				CPUWrite : 1;				///<Pozwala na zapis tekstury przez CPU.
	bool				AllowShareResource : 1;		///<Pozwala na dost�p do zasoby z wielu API graficznych i pomi�dzy kontekstami.
	bool				IsCubeMap : 1;				///<Nale�y ustawi� je�eli tekstura jest cubemap�.
	uint8				NumSamples;					///<Liczba pr�bek w przypadku stosowania multisamplingu.
	uint16				SamplesQuality;				///<Jako�� pr�bek przy multisamplingu.
	TextureType			TextureType;				///<Typ tekstury (liczba wymiar�w, multsampling). Tekstura nie mo�e by� inna ni� dwuwymiarowa (mo�e by� tablic�).
	ResourceFormat		ColorBuffFormat;			///<Format bufora kolor�w.
	DepthStencilFormat	DepthStencilFormat;			///<Format bufora g��boko�ci i stencilu.
	ResourceUsage		Usage;						///<Spos�b u�ycia render targetu. Wp�ywa na optymalizacje u�o�enia w pami�ci.

	/**@brief Ustawia domy�lne warto�ci deskryptora.
	
	Ustawiane s� pola CPURead, CPUWrite, AllowShareResource, IsCubeMap, Usage.
	Te zmienne s� u�ywane rzadko i dlatego powinny mie� takie warto�ci, �eby nie trzeba by�o ich jawnie ustawia�.
	Pozosta�e warto�ci u�ytkownik i tak musi zdefiniowa� samemu, wi�c nie ma co nadk�ada� pracy.
	
	Pola NumSamples i SamplesQuality s� ignorowane, je�eli TextureType nie zosta� ustawiony na tekstur� z multisamplingiem.
	Pole ArraySize jest ignorowane, je�eli tekstura nie jest tablic�.*/
	RenderTargetDescriptor()
	{
		ArraySize = 1;
		CPURead = 0;
		CPUWrite = 0;
		AllowShareResource = 0;
		IsCubeMap = 0;
		Usage = ResourceUsage::RESOURCE_USAGE_DEFAULT;
	}

	/**@brief Tworzy strukture TextureInfo wype�nion� danymi zgodnymi z deskryptorem RenderTargetu.
	
	@attention Funkcja nie ustawia formatu tekstury. Nie da si� wywnioskowa� formatu na podstawie deskryptora.*/
	TextureInfo		CreateTextureInfo() const
	{
		TextureInfo texInfo;
		texInfo.TextureWidth = TextureWidth;
		texInfo.TextureHeight = TextureHeight;
		texInfo.ArraySize = ArraySize;
		texInfo.CPURead = CPURead;
		texInfo.CPUWrite = CPUWrite;
		texInfo.AllowShareResource = AllowShareResource;
		texInfo.IsCubeMap = IsCubeMap;
		texInfo.TextureType = TextureType;
		texInfo.Usage = Usage;

		return texInfo;
	}
};

/**@brief Klasa dla render target�w.
@ingroup RenderTargets
@ingroup Resources
@ingroup GraphicAPI

Klasa umo�liwia pobranie jednej z tekstur sk�adowych i udost�pnienie dla shader�w.
Je�eli API graficzne nie pozwala na oddzielne trzymanie bufora g��boko�ci i stencilu,
to mo�e tu by� przechowywany ten sam obiekt. Ewentualnie mog� by� to dwa obiekty,
kt�re przechowuj� inny widok, ale fizycznie odwo�uj� si� do tej samej pami�ci.*/
class RenderTargetObject : public IRenderTarget
{
	RTTR_ENABLE( IRenderTarget );
	RTTR_REGISTRATION_FRIEND;
private:
protected:
	ResourcePtr< TextureObject >	m_colorBuffer;			///<Pozwala na dost�p do bufora kolor�w dla innych obiekt�w. Mo�e by� nullptrem.
	ResourcePtr< TextureObject >	m_depthBuffer;			///<Pozwala na dost�p do bufora g��boko�ci. Mo�e by� nullptrem.
	ResourcePtr< TextureObject >	m_stencilBuffer;		///<Pozwala na dost�p do bufora stencil. Mo�e by� nulltrem.
public:
	RenderTargetObject( TextureObject* colorBuffer, TextureObject* depthBuffer, TextureObject* stencilBuffer );
	virtual ~RenderTargetObject();

	inline TextureObject*		GetColorBuffer()			{ return m_colorBuffer.Ptr(); }		///<Zwraca obiekt bufora kolor�w.
	inline TextureObject*		GetDepthBuffer()			{ return m_depthBuffer.Ptr(); }		///<Zwraca obiekt bufora g��boko�ci.
	inline TextureObject*		GetStencilBuffer()			{ return m_stencilBuffer.Ptr(); }		///<Zwraca obiekt bufora stencilu.

	virtual std::string			GetResourceName	() const override;	///<@todo RenderTargety powinny mie� swoje nazwy.
};


//----------------------------------------------------------------------------------------------//
//								BufferObject													//
//----------------------------------------------------------------------------------------------//

/**@brief Obiekt opakowuj�cy bufor.
@ingroup Buffers
@ingroup Resources
@ingroup GraphicAPI

Bufor mo�e by� zar�wno buforem wierzcho�k�w, indeks�w jak i sta�ych.
*/
class BufferObject : public IBuffer
{
	RTTR_ENABLE( IBuffer )
	friend ObjectDeleter<BufferObject>;
protected:
	unsigned int		m_elementSize;			///<Rozmiar elementu.
	unsigned int		m_elementCount;			///<Liczba element�w.

	~BufferObject() = default;
public:
	BufferObject( unsigned int elementSize, unsigned int elementCount );

	inline unsigned int GetStride()				{ return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int	GetElementSize()		{ return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int GetElementCount()		{ return m_elementCount; }		///<Zwraca liczb� element�w w buforze.

	virtual std::string	GetResourceName	() const override { return GetDescriptor().GetName(); }
};

