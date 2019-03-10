/**
@file Texture.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "Texture.h"



RTTR_REGISTRATION
{

	rttr::registration::enumeration< sw::TextureType >( "TextureType" )
	(
		rttr::value( "Buffer", sw::TextureType::TEXTURE_TYPE_BUFFER ),
		rttr::value( "Texture 1D", sw::TextureType::TEXTURE_TYPE_TEXTURE1D ),
		rttr::value( "Texture 1D Array", sw::TextureType::TEXTURE_TYPE_TEXTURE1D_ARRAY ),
		rttr::value( "Texture 2D", sw::TextureType::TEXTURE_TYPE_TEXTURE2D ),
		rttr::value( "Texture 2D Array", sw::TextureType::TEXTURE_TYPE_TEXTURE2D_ARRAY ),
		rttr::value( "Texture 2D Multisample", sw::TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE ),
		rttr::value( "Texture 2D Multisample Array", sw::TextureType::TEXTURE_TYPE_TEXTURE2D_MULTISAMPLE_ARRAY ),
		rttr::value( "Texture 3D", sw::TextureType::TEXTURE_TYPE_TEXTURE3D )
	);

	rttr::registration::enumeration< sw::MipMapFilter >( "sw::MipMapFilter" )
	(
		rttr::value( "Bell", sw::MipMapFilter::Bell ),
		rttr::value( "Blackman", sw::MipMapFilter::Blackman ),
		rttr::value( "Box", sw::MipMapFilter::Box ),
		rttr::value( "bSpline", sw::MipMapFilter::bSpline ),
		rttr::value( "Catmullrom", sw::MipMapFilter::Catmullrom ),
		rttr::value( "Gaussian", sw::MipMapFilter::Gaussian ),
		rttr::value( "Kaiser", sw::MipMapFilter::Kaiser ),
		rttr::value( "Lanczos12", sw::MipMapFilter::Lanczos12 ),
		rttr::value( "Lanczos3", sw::MipMapFilter::Lanczos3 ),
		rttr::value( "Lanczos4", sw::MipMapFilter::Lanczos4 ),
		rttr::value( "Lanczos6", sw::MipMapFilter::Lanczos6 ),
		rttr::value( "Mitchell", sw::MipMapFilter::Mitchell ),
		rttr::value( "QuadraticAproximation", sw::MipMapFilter::QuadraticAproximation ),
		rttr::value( "QuadraticInterpolation", sw::MipMapFilter::QuadraticInterpolation ),
		rttr::value( "QuadraticMix", sw::MipMapFilter::QuadraticMix ),
		rttr::value( "Tent", sw::MipMapFilter::Tent ),
		rttr::value( "No filtering", sw::MipMapFilter::Unknown )
	);

	rttr::registration::class_< sw::TextureInfo >( "sw::TextureInfo" )
		.property_readonly( "Width", &sw::TextureInfo::GetWidth )
		.property_readonly( "Height", &sw::TextureInfo::GetHeight )
		.property_readonly( "ArraySize", &sw::TextureInfo::GetArraySize )
		.property_readonly( "CPUReadable", &sw::TextureInfo::IsCPUReadable )
		.property_readonly( "CPUWritable", &sw::TextureInfo::IsCPUWriteable )
		.property_readonly( "SharedResource", &sw::TextureInfo::IsSharedResource )
		.property_readonly( "CubeMap", &sw::TextureInfo::IsCubeMapTex )
		.property_readonly( "GeneratedMipMaps", &sw::TextureInfo::GenMipMaps )
		.property_readonly( "TextureType", &sw::TextureInfo::TextureType )
		.property_readonly( "Usage", &sw::TextureInfo::Usage )
		.property_readonly( "Format", &sw::TextureInfo::Format )
		.property_readonly( "MipMapFilter", &sw::TextureInfo::MipMapFilter )
		.property_readonly( "MipMapsLevels", &sw::TextureInfo::GetMipLevels )
		.property_readonly( "FilePath", &sw::TextureInfo::GetPath );

	rttr::registration::class_< sw::Texture >( "sw::Texture" )
		.property_readonly( "Descriptor", &sw::Texture::GetDescriptor ) BIND_AS_PTR;
}


//----------------------------------------------------------------------------------------------//
//								Texture													//
//----------------------------------------------------------------------------------------------//



namespace sw
{

/**@brief Porównuje ze soba dwa obiekty tekstur.

Obiekty s¹ takie same, kiedy odwo³uj¹ siê do tego samego pliku.
*/
bool		Texture::operator==( Texture& object )
{
	if( this->GetFilePath().String() == object.GetFilePath().String() )
		return true;
	return false;
}

/**@brief Porównuje ze soba dwa obiekty tekstur.

Obiekty s¹ takie same, kiedy odwo³uj¹ siê do tego samego pliku.
*/
bool		Texture::operator==( const std::wstring& fileName )
{
	typedef std::codecvt_utf8<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;
	auto convertedFileName = converter.to_bytes( fileName );

	if( this->GetFilePath().String() == convertedFileName )
		return true;
	return false;
}


}	// sw