#pragma once
/**
@file MeshResources.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.

@brief Plik zawiera deklaracje formatów wierzcho³ków oraz klas zawieraj¹cych assety shadery itp.
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


class BufferObject;
class TextureObject;
class VertexShader;
class PixelShader;


/*
// W buforze wierzcho³ków znajduj¹ siê elementy typu VERT_INDEX.
// Definicja typu VERT_INDEX znajduje siê w pliku macros_switches.h i wygl¹da tak:

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
	TEX_DIFFUSE			///<Tekstura dla kana³u diffuse
	, TEX_SPECULAR		///<Tekstura dla kana³u specular
	, TEX_EMISSIVE		///< Texture for emmisive channel
	, TEX_BUMP_MAP		///<Bump mapa
	, TEX_DISPLACEMENT_MAP		///<Tekstura przemieszczeñ wierzcho³ków, w przypadku u¿ywania teselacji wierzcho³ków
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

/**@brief Struktura u¿ywana do tworzenia render targetu.
@ingroup RenderTargets*/
struct RenderTargetDescriptor
{
	uint16				TextureWidth;				///<Szerokoœæ tekstury w pikselach.
	uint16				TextureHeight;				///<Wysokoœæ tekstury w pikselach.
	uint16				ArraySize;					///<Liczba elementów tablicy.
	bool				CPURead : 1;				///<Pozwala na odczyt tekstury przez CPU.
	bool				CPUWrite : 1;				///<Pozwala na zapis tekstury przez CPU.
	bool				AllowShareResource : 1;		///<Pozwala na dostêp do zasoby z wielu API graficznych i pomiêdzy kontekstami.
	bool				IsCubeMap : 1;				///<Nale¿y ustawiæ je¿eli tekstura jest cubemap¹.
	uint8				NumSamples;					///<Liczba próbek w przypadku stosowania multisamplingu.
	uint16				SamplesQuality;				///<Jakoœæ próbek przy multisamplingu.
	TextureType			TextureType;				///<Typ tekstury (liczba wymiarów, multsampling). Tekstura nie mo¿e byæ inna ni¿ dwuwymiarowa (mo¿e byæ tablic¹).
	ResourceFormat		ColorBuffFormat;			///<Format bufora kolorów.
	DepthStencilFormat	DepthStencilFormat;			///<Format bufora g³êbokoœci i stencilu.
	ResourceUsage		Usage;						///<Sposób u¿ycia render targetu. Wp³ywa na optymalizacje u³o¿enia w pamiêci.

	/**@brief Ustawia domyœlne wartoœci deskryptora.
	
	Ustawiane s¹ pola CPURead, CPUWrite, AllowShareResource, IsCubeMap, Usage.
	Te zmienne s¹ u¿ywane rzadko i dlatego powinny mieæ takie wartoœci, ¿eby nie trzeba by³o ich jawnie ustawiaæ.
	Pozosta³e wartoœci u¿ytkownik i tak musi zdefiniowaæ samemu, wiêc nie ma co nadk³adaæ pracy.
	
	Pola NumSamples i SamplesQuality s¹ ignorowane, je¿eli TextureType nie zosta³ ustawiony na teksturê z multisamplingiem.
	Pole ArraySize jest ignorowane, je¿eli tekstura nie jest tablic¹.*/
	RenderTargetDescriptor()
	{
		ArraySize = 1;
		CPURead = 0;
		CPUWrite = 0;
		AllowShareResource = 0;
		IsCubeMap = 0;
		Usage = ResourceUsage::RESOURCE_USAGE_DEFAULT;
	}

	/**@brief Tworzy strukture TextureInfo wype³nion¹ danymi zgodnymi z deskryptorem RenderTargetu.
	
	@attention Funkcja nie ustawia formatu tekstury. Nie da siê wywnioskowaæ formatu na podstawie deskryptora.*/
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

/**@brief Klasa dla render targetów.
@ingroup RenderTargets
@ingroup Resources
@ingroup GraphicAPI

Klasa umo¿liwia pobranie jednej z tekstur sk³adowych i udostêpnienie dla shaderów.
Je¿eli API graficzne nie pozwala na oddzielne trzymanie bufora g³êbokoœci i stencilu,
to mo¿e tu byæ przechowywany ten sam obiekt. Ewentualnie mog¹ byæ to dwa obiekty,
które przechowuj¹ inny widok, ale fizycznie odwo³uj¹ siê do tej samej pamiêci.*/
class RenderTargetObject : public IRenderTarget
{
	RTTR_ENABLE( IRenderTarget );
	RTTR_REGISTRATION_FRIEND;
private:
protected:
	ResourcePtr< TextureObject >	m_colorBuffer;			///<Pozwala na dostêp do bufora kolorów dla innych obiektów. Mo¿e byæ nullptrem.
	ResourcePtr< TextureObject >	m_depthBuffer;			///<Pozwala na dostêp do bufora g³êbokoœci. Mo¿e byæ nullptrem.
	ResourcePtr< TextureObject >	m_stencilBuffer;		///<Pozwala na dostêp do bufora stencil. Mo¿e byæ nulltrem.
public:
	RenderTargetObject( TextureObject* colorBuffer, TextureObject* depthBuffer, TextureObject* stencilBuffer );
	virtual ~RenderTargetObject();

	inline TextureObject*		GetColorBuffer()			{ return m_colorBuffer.Ptr(); }		///<Zwraca obiekt bufora kolorów.
	inline TextureObject*		GetDepthBuffer()			{ return m_depthBuffer.Ptr(); }		///<Zwraca obiekt bufora g³êbokoœci.
	inline TextureObject*		GetStencilBuffer()			{ return m_stencilBuffer.Ptr(); }		///<Zwraca obiekt bufora stencilu.

	virtual std::string			GetResourceName	() const override;	///<@todo RenderTargety powinny mieæ swoje nazwy.
};


//----------------------------------------------------------------------------------------------//
//								BufferObject													//
//----------------------------------------------------------------------------------------------//

/**@brief Obiekt opakowuj¹cy bufor.
@ingroup Buffers
@ingroup Resources
@ingroup GraphicAPI

Bufor mo¿e byæ zarówno buforem wierzcho³ków, indeksów jak i sta³ych.
*/
class BufferObject : public IBuffer
{
	RTTR_ENABLE( IBuffer )
	friend ObjectDeleter<BufferObject>;
protected:
	unsigned int		m_elementSize;			///<Rozmiar elementu.
	unsigned int		m_elementCount;			///<Liczba elementów.

	~BufferObject() = default;
public:
	BufferObject( unsigned int elementSize, unsigned int elementCount );

	inline unsigned int GetStride()				{ return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int	GetElementSize()		{ return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int GetElementCount()		{ return m_elementCount; }		///<Zwraca liczbê elementów w buforze.

	virtual std::string	GetResourceName	() const override { return GetDescriptor().GetName(); }
};

