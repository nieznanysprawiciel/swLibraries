#pragma once
/**
@file LoadingResult.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/Resources/ResourceObject.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"

#include "swCommonLib/Common/Exceptions/Exception.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"

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
	LoadingResult		( ResourcePointer resource );
	LoadingResult		( std::string error );
	LoadingResult		( ExceptionPtr error );
	LoadingResult		( std::string error, ExceptionPtr warnings );
	LoadingResult		( ExceptionPtr error, ExceptionPtr warnings );
	LoadingResult		( AssetsVec assets, ExceptionPtr warnings );
	LoadingResult		( ExceptionPtr error, const ErrorsCollector& warnings );

};

//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
inline LoadingResult::LoadingResult			( ResourcePointer resource )
	: Assets( AssetsVec( { resource } ) )
{}

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

// ================================ //
//
inline LoadingResult::LoadingResult			( AssetsVec assets, ExceptionPtr warnings )
	: Assets( std::move( assets ) )
	, Warnings( warnings )
{}

// ================================ //
//
inline LoadingResult::LoadingResult			( ExceptionPtr error, const ErrorsCollector& warnings )
	: Assets( Nullable< AssetsVec >( error ) )
	, Warnings( warnings.GetException() )
{}

}	// sw


