#pragma once
/**
@file MaterialInfo.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"



namespace sw
{

/// Maximal number of textures in material.
#define MAX_MATERIAL_TEXTURES		5


/**@brief Structure describes additional buffers that must be provided for Material.
@ingroup Materials*/
struct ParametricBufferInfo
{
	ShaderType		ShaderType;		///< Shader that should have this buffer bound.
	TypeID  		BufferType;		///< Type of buffer, which must be bound to material by actor.
	uint32			BufferSize;		///< Buffer size in bytes.

    // ================================ //
    //
	ParametricBufferInfo()
		: BufferType( rttr::type::get_by_name( "" ) )
	{}

	std::string		GetBufferType		() const { return BufferType.get_name().to_string(); }
	void			SetBufferType		( std::string name );
};



/**@brief Material description.

This structure describes parameters buffers, that this material requires.

@ingroup Materials*/
struct MaterialInfo
{
	std::vector< ParametricBufferInfo >		ParametricBuffers;		///< Description of additional buffers that must be provided for this M<aterial.
	UPtr< ShadingModelBase >				ShadingData;			///< Stores shading model parameters. @see ShadingModelData


    // ================================ //
    //
	MaterialInfo	( std::vector< ParametricBufferInfo >&& addBuff, UPtr< ShadingModelBase >&& shadModel );
	~MaterialInfo	();
};



//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline MaterialInfo::MaterialInfo           ( std::vector< ParametricBufferInfo >&& addBuff, UPtr< ShadingModelBase >&& shadModel )
{
    ParametricBuffers = std::move( addBuff );
	ShadingData = std::move( shadModel );
}

// ================================ //
//
inline MaterialInfo::~MaterialInfo	()
{}

// ================================ //
//
inline void			ParametricBufferInfo::SetBufferType( std::string name )
{
	auto newType = rttr::type::get( name );
	if( newType.is_valid() )
		BufferType = newType;
}

//====================================================================================//
//			Operators	
//====================================================================================//

// ================================ //
//
inline bool                 operator==          ( const ParametricBufferInfo& info1, const ParametricBufferInfo& info2 )
{
    return std::tie( info1.BufferSize, info1.ShaderType, info1.BufferType )
        == std::tie( info2.BufferSize, info2.ShaderType, info2.BufferType );
}

// ================================ //
//
inline bool                 operator!=          ( const ParametricBufferInfo& info1, const ParametricBufferInfo& info2 )
{
    return !( info1 == info2 );
}



}	// sw

