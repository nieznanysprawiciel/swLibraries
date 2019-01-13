#pragma once
/**
@file Texture.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/Common/ObjectDeleter.h"
#include "swCommonLib/System/Path.h"
#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/MemoryChunk.h"

#include "swGraphicAPI/Resources/ResourcePtr.h"
#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"


//----------------------------------------------------------------------------------------------//
//								TextureObject													//
//----------------------------------------------------------------------------------------------//

/**@defgroup Textures Textures
@ingroup Resources

@todo Rename TextureObject to Texture. TextureObject is too long name.
*/

/**@brief Textures filtering modes.

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





/** @brief Base class for textures.
@ingroup Textures
@ingroup Resources
@ingroup GraphicAPI

This class is platform independent. Inherit it while implementing chosen graphic API.*/
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

	virtual const filesystem::Path&		GetFilePath		() const = 0;		///< Returns name of file, from which this object was created.

	/**@brief Updates texture data on graphic card.
	Note that size of dataPtr memory must large be enough to fill requested miplevel and array idx.
	You can always check @ref GetDescriptor function to get desired info.

	@todo Do something with this when rendering will use event queues.*/
	virtual bool						UpdateData		( uint8* dataPtr, uint16 mipLevel, uint16 arrayIdx ) = 0;

	/**@brief Copies texture data from graphic card to memory chunk.*/
	virtual MemoryChunk					CopyData		() const = 0;
	virtual const TextureInfo&			GetDescriptor	() const = 0;		///< Gets texture descriptor.

	virtual std::string					GetResourceName	() const override { return GetFilePath().String(); }

	inline bool operator==( TextureObject& object );
	inline bool operator==( const std::wstring& file_name );
};

