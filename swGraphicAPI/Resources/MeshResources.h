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

#include <DirectXMath.h>


//definicje
/** @def WRONG_ID
B��dny identyfikator assetu w klasie @ref ResourceObject.*/
#define WRONG_ID						0

/**@defgroup Resources Resources
@ingroup ResourcesManagment
@ingroup GraphicAPI
@brief Niskopoziomowe zasoby zwi�zane z api graficznym.

Zasoby s� silnie zale�ne od u�ywanej platformy sprz�towej. W celu oddzielenia referencji do
API graficznego od @ref EngineCore, wszystkie obiekty silnika u�ywaj� jedynie klas bazowych, kt�re
s� implementowane przez poszczeg�lne API graficzne. Aby zobaczy� konkretne implementacje tych klas
zobacz @ref GraphicAPI.

Zasoby nigdy nie s� tworzone bezpo�rednio. Zamiast tego u�ywa si� klasy @ref ResourcesFactory, kt�r�
implementuje konkretne API graficzne.

Poniewa� zasoby mog� by� wsp�dzielone przez wiele obiekt�w w silniku, istnieje mechanizm zliczania
odwo�a� do obiekt�w implementowany przez klas� @ref ResourceObject.*/

class AssetsManager;
struct ModelPart;
class BufferObject;
class TextureObject;
class VertexShader;
class PixelShader;
struct MeshPartObject;
struct MaterialObject;

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
//								TextureObject													//
//----------------------------------------------------------------------------------------------//

/**@defgroup Textures Textures
@ingroup Resources
*/

/**@brief Tryby filtrowania tekstur.

Poni�sze tryby filtrowania s� u�ywane przy tworzeniu mipmap.
Istnieje jeszcze drugi etap filtrowania przy pr�bkowania w pixel shaderze,
do kt�rego odnosi si� inna enumeracja.

@ingroup Textures
*/
enum class MipMapFilter : short
{
	Box = 0,		///<
	Tent,			///< 
	Bell,			///<
	bSpline,		///<
	Mitchell,		///<
	Lanczos3,		///<
	Blackman,		///<
	Lanczos4,		///<
	Lanczos6,		///<
	Lanczos12,		///<
	Kaiser,			///<
	Gaussian,		///<
	Catmullrom,		///<
	QuadraticInterpolation,		///<
	QuadraticAproximation,		///<
	QuadraticMix,				///<

	Unknown						///<
};


/**@brief Deskryptor tekstury.

@ingroup Textures
*/
struct TextureInfo
{
	uint16				TextureWidth;				///< Szeroko�� tekstury w pikselach.
	uint16				TextureHeight;				///< Wysoko�� tekstury w pikselach.
	uint16				ArraySize;					///< Liczba element�w tablicy.
	bool				CPURead : 1;				///< Pozwala na odczyt tekstury przez CPU.
	bool				CPUWrite : 1;				///< Pozwala na zapis tekstury przez CPU.
	bool				AllowShareResource : 1;		///< Pozwala na dost�p do zasoby z wielu API graficznych i pomi�dzy kontekstami.
	bool				IsCubeMap : 1;				///< Nale�y ustawi� je�eli tekstura jest cubemap�.
	bool				GenerateMipMaps : 1;		///< Automatyczne generowanie mipmap.
	TextureType			TextureType;				///< Typ tekstury (liczba wymiar�w, multsampling). Na razie tekstura nie mo�e by� inna ni� dwuwymiarowa (mo�e by� tablic�).
	ResourceUsage		Usage;						///< Spos�b u�ycia render targetu. Wp�ywa na optymalizacje u�o�enia w pami�ci.
	ResourceFormat		Format;						///< Format tekstury (liczba kana��w, liczba bit�w na kana� itp)
	MipMapFilter		MipMapFilter;				///< Tryb filtrowania tekstury. U�ywany tylko je�eli ustawiono GenerateMipMaps na true.
	uint16				MipMapLevels;				///< Liczba poziom�w mipmap. 1 oznacza tylko tekstur� oryginaln�.
	uint16				CutOffMipMaps;				///< Usuwa podan� liczb� poziom�w mipmap. Przydatne gdy nie potrzebujemy tekstur zbyt wysokiej rozdzielczo�ci (np. stosuj�c dynamiczny LoD).
													///< Ustawienie warto�ci 1 oznacza, �e oryginalna tekstura zostanie zast�piona pierwsz� mipmap� w kolejno�ci.

	uint32				MemorySize;					///< Pami�� zajmowana przez tekstur�.
	filesystem::Path	FilePath;					///< �cie�ka do pliku z tekstur� lub jej nazwa.
	
	TextureInfo()
	{
		ArraySize = 1;
		CPURead = false;
		CPUWrite = false;
		AllowShareResource = false;
		IsCubeMap = false;
		GenerateMipMaps = false;
		Usage = ResourceUsage::RESOURCE_USAGE_DEFAULT;
		MipMapFilter = MipMapFilter::Unknown;
		MipMapLevels = 1;
		CutOffMipMaps = 0;
		TextureType = TextureType::TEXTURE_TYPE_TEXTURE2D;
		MemorySize = 0;
	}

private:
	RTTR_REGISTRATION_FRIEND;
	
	int		GetWidth		()		{ return TextureWidth; }
	int		GetHeight		()		{ return TextureHeight; }
	int		GetArraySize	()		{ return ArraySize; }
	bool	IsCPUReadable	()		{ return CPURead; }
	bool	IsCPUWriteable	()		{ return CPUWrite; }
	bool	IsSharedResource()		{ return AllowShareResource; }
	bool	IsCubeMapTex	()		{ return IsCubeMap; }
	bool	GenMipMaps		()		{ return GenerateMipMaps; }
	int		GetMipLevels	()		{ return MipMapLevels; }

	std::string		GetPath	()		{ return FilePath.String(); }
};

/** @brief Klasa przechowuj�ca tekstury.
@ingroup Textures
@ingroup Resources
@ingroup GraphicAPI

Klasa bazowa, kt�ra b�dzie u�ywana przez obiekty silnika.
Powinny po niej odziedziczy� obiekty konkretnego API graficznego,
�eby zaimplementowa� najwa�niejsze funkcjonalno�ci.*/
class TextureObject : public ResourceObject
{
	RTTR_ENABLE( ResourceObject );
	friend ObjectDeleter<TextureObject>;
private:
protected:
	/// �eby unikn�� pomy�ki, obiekt mo�e by� kasowany tylko przez AssetsManager. Zapewnia to ObjectDeleter.
	virtual ~TextureObject() = default;
public:
	TextureObject() : ResourceObject( 0 ) {}

	virtual const filesystem::Path&		GetFilePath		() const = 0;		///<Zwraca nazw� pliku, kt�ry pos�u�y� do stworzenia obiektu

	virtual MemoryChunk					CopyData		() const = 0;		///<Kopiuje dane z bufora i umieszcza je w zwracanym MemoryChunku.
	virtual const TextureInfo&			GetDescriptor	() const = 0;		///<Pozwala pobra� deskrytpro tekstury.

	virtual std::string					GetResourceName	() const override { return GetFilePath().String(); }

	inline bool operator==( TextureObject& object );
	inline bool operator==( const std::wstring& file_name );
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
//								ShaderInputLayout												//
//----------------------------------------------------------------------------------------------//

/**@defgroup Shaders Shaders
@ingroup Resources
*/

/**@brief Klasa przechowuje layout wierzcho�ka trafiaj�cego do
vertex shadera.
@ingroup Shaders
@ingroup Buffers
@ingroup Resources*/
class ShaderInputLayout : public IShaderInputLayout
{
	RTTR_ENABLE( IShaderInputLayout );
	friend ObjectDeleter< ShaderInputLayout >;
private:
protected:
	virtual ~ShaderInputLayout() = default;
public:
	ShaderInputLayout() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

/**@brief Klasa przechowuje opis layoutu wierzcho�ka, na podstawie kt�rego
tworzony jest obiekt layoutu.
@ingroup Buffers
@ingroup Shaders
@ingroup Resources*/
class InputLayoutDescriptor
{
private:
	std::wstring				m_inputLayoutName;
protected:
public:
	InputLayoutDescriptor( const std::wstring& layoutName ) : m_inputLayoutName( layoutName ){}
	virtual ~InputLayoutDescriptor() = default;

	virtual void		AddRow		( const char* semanticName, ResourceFormat format, unsigned int inputSlot, unsigned int byteOffset, bool perInstance, unsigned int instanceDataStep ) = 0;

	std::wstring&		GetName		() { return m_inputLayoutName; }
};


/**@brief Typ shadera.
@ingroup Shaders*/
enum class ShaderType : uint8
{
	VertexShader				= 0x01,
	PixelShader					= 0x02,
	GeometryShader				= 0x04,
	TesselationControlShader	= 0x08,
	TesselationEvaluationShader	= 0x10,
	ComputeShader				= 0x20
};

//----------------------------------------------------------------------------------------------//
//								VertexShader													//
//----------------------------------------------------------------------------------------------//

/** @brief Klasa przechowuj�ca vertex shader.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class VertexShader : public IShader
{
	RTTR_ENABLE( IShader );
	friend ObjectDeleter< VertexShader >;
private:
protected:
	~VertexShader() = default;
public:
	VertexShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

//----------------------------------------------------------------------------------------------//
//								PixelShader														//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuj�ca pixel shader.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class PixelShader : public IShader
{
	RTTR_ENABLE( IShader );
	friend ObjectDeleter< PixelShader >;
private:
protected:
	~PixelShader() = default;
public:
	PixelShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

//----------------------------------------------------------------------------------------------//
//								GeometryShader													//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuj�ca pixel shader.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class GeometryShader : public IShader
{
	RTTR_ENABLE( IShader );
	friend ObjectDeleter<GeometryShader>;
private:
protected:
	~GeometryShader() = default;
public:
	GeometryShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

//----------------------------------------------------------------------------------------------//
//								ControlShader													//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuj�ca pixel shader.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class ControlShader : public IShader
{
	RTTR_ENABLE( IShader );
	friend ObjectDeleter< ControlShader >;
private:
protected:
	~ControlShader() = default;
public:
	ControlShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

//----------------------------------------------------------------------------------------------//
//								EvaluationShader												//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuj�ca pixel shader.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class EvaluationShader : public IShader
{
	RTTR_ENABLE( IShader );
	friend ObjectDeleter< EvaluationShader >;
private:
protected:
	~EvaluationShader() = default;
public:
	EvaluationShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

//----------------------------------------------------------------------------------------------//
//								ComputeShader													//
//----------------------------------------------------------------------------------------------//

/**@brief Klasa przechowuj�ca compute shader
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class ComputeShader : public IShader
{
	RTTR_ENABLE( IShader );
	friend ObjectDeleter<ComputeShader>;
private:
protected:
	~ComputeShader() = default;
public:
	ComputeShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
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

//----------------------------------------------------------------------------------------------//
//								MaterialObject													//
//----------------------------------------------------------------------------------------------//


/**@brief Struktura przechowuj�ca materia�.
@ingroup Resources

@deprecated New material structure is coming soon

DirectX 11 nie ma w�asnych obiekt�w na materia�y, poniewa� nie ma ju� domy�lnego
potoku przetwarzania na karcie graficznej. Na wszystko trzeba napisa� shader i dostarcza
mu si� takie dane, jakie si� chce dostarczy�. Dlatego informacja o materia�ach b�dzie
przekazywana z buforze sta�ych.

Struktura zachowuje si� jak asset w zwi�zku z czym mo�e
by� wsp�dzielona przez wiele obiekt�w. Z tego wzgl�du nie mo�na jej u�y� bezpo�rednio w ConstantPerMesh,
poniewa� nie chcemy przekazywa� do bufora sta�ych zmiennych odziedziczonych po ResourceObject.
Zamiast tego trzeba t� strukture przepisa�.

Zwracam uwag�, �e tylko kana� Diffuse jest wektorem 4 wymiarowym, w kt�rym sk�adowa w jest odpowiedzialna
za przezroczysto��. Pozosta�e s� takie tylko dlatego, �e jest to domy�lny format przechowywania danych 
w rejestrach karty graficznej i przyspiesza to operacj� kopiowania.
@see ConstantPerFrame
*/
struct MaterialObject : public ResourceObject
{
	RTTR_ENABLE( ResourceObject );
public:
	friend ObjectDeleter<MaterialObject>;

	DirectX::XMFLOAT4		Diffuse;		//Sk�adowa przezroczysto�ci odnosi si� do ca�ego materia�u
	DirectX::XMFLOAT4		Ambient;
	DirectX::XMFLOAT4		Specular;
	DirectX::XMFLOAT4		Emissive;
	float					Power;

	MaterialObject( unsigned int id = WRONG_ID ) : ResourceObject( id ){}
	MaterialObject( const MaterialObject* material );

	void SetNullMaterial();

	virtual std::string	GetResourceName	() const override { return ""; }
};


