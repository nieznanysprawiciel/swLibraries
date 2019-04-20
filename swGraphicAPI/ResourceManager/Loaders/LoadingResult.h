#pragma once
/**
@file LoadingResult.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"

#include "swCommonLib/Common/Exceptions/Exception.h"

#include <vector>


namespace sw
{

typedef std::vector< ResourcePointer > AssetsVec;



/**@brief Structure returned by loader.
@ingroup Loaders*/
struct LoadingResult
{
	Nullable< AssetsVec >		Assets;			///< Contains all assets loaded in @ref Load call or errors in case of fail.
	ExceptionPtr				Warnings;		///< Contains all warining that occured during loading.

public:

	LoadingResult		() = default;
	LoadingResult		( std::string error );
	LoadingResult		( ExceptionPtr error );
	LoadingResult		( std::string error, ExceptionPtr warnings );
	LoadingResult		( ExceptionPtr error, ExceptionPtr warnings );

};

//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
inline LoadingResult::LoadingResult			( std::string error )
	: Assets( Nullable< AssetsVec >( error ) )
{}

// ================================ //
//
inline LoadingResult::LoadingResult			( ExceptionPtr error )
	: Assets( Nullable< AssetsVec >( error ) )
{}

// ================================ //
//
inline LoadingResult::LoadingResult			( ExceptionPtr error, ExceptionPtr warnings )
	: Assets( Nullable< AssetsVec >( error ) )
	, Warnings( warnings )
{}

// ================================ //
//
inline LoadingResult::LoadingResult			( std::string error, ExceptionPtr warnings )
	: Assets( Nullable< AssetsVec >( error ) )
	, Warnings( warnings )
{}

}	// sw


