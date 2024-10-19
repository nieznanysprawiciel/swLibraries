/**
@file Texture.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "swCommonLib/Common/Converters.h"

#include "Texture.h"

#include "swCommonLib/Common/Converters/Convert.h"



RTTR_REGISTRATION
{

	rttr::registration::enumeration< sw::TextureType >( "TextureType" )
	(
		rttr::value( "Buffer", sw::TextureType::Buffer ),
		rttr::value( "Texture 1D", sw::TextureType::Texture1D ),
		rttr::value( "Texture 1D Array", sw::TextureType::TextureArray1D ),
		rttr::value( "Texture 2D", sw::TextureType::Texture2D ),
		rttr::value( "Texture 2D Array", sw::TextureType::TextureArray2D ),
		rttr::value( "Texture 2D Multisample", sw::TextureType::Texture2DMultisample ),
		rttr::value( "Texture 2D Multisample Array", sw::TextureType::TextureArray2DMultisample ),
		rttr::value( "Texture 3D", sw::TextureType::Texture3D )
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

/**@brief Compares 2 Texture objects. Textures are the same when they refer to the same file.*/
bool		Texture::operator==( Texture& object )
{
	if( this->GetFilePath().String() == object.GetFilePath().String() )
		return true;
	return false;
}

/**@brief Compares 2 Texture objects. Textures are the same when they refer to the same file.*/
bool		Texture::operator==( const std::wstring& fileName )
{
	if( this->GetFilePath().String() == Convert::ToString(fileName) )
		return true;
	return false;
}


}	// sw