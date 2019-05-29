#pragma once
/**
@file ShaderInitData.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/RTTR.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include "swGraphicAPI/Resources/Shaders/Shaders.h"

#include <string>



namespace sw
{


/**@brief Create shader of given type from file path.

Note: File path will be passed as second parameter to creator function so is ommited here.
@ingroup Shaders*/
struct ShaderInitData : public IAssetCreateInfo
{
	RTTR_ENABLE( IAssetCreateInfo );
public:

	std::string			EntryFunction;	///< Name of shader entry point function. "main" by default.
	ShaderType			Type;			///< Type of shader to create.



// ================================ //
//
	ShaderInitData( ShaderType type )
		:	Type( type )
		,	EntryFunction( "main" )
	{}

	virtual TypeID		GetAssetType	() const override;

public:

	static ShaderType	GetFromTypeID	( TypeID type );
};


/**@brief Create shader from string containing source code.
@ingroup Shaders*/
struct ShaderCodeInitData : public ShaderInitData
{
	RTTR_ENABLE( ShaderInitData );
public:

	std::string			SourceCode;


// ================================ //
//
	ShaderCodeInitData( ShaderType type )
		:	ShaderInitData( type )
	{}

	ShaderCodeInitData( ShaderType type, std::string sourceCode )
		:	ShaderInitData( type )
		,	SourceCode( std::move( sourceCode ) )
	{}

};



}	// sw

