#pragma once
/**
@file LoadingContext.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/LoadingResult.h"

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swCommonLib/Common/Exceptions/Common/InvalidCodeLogicException.h"



namespace sw
{


/**@brief Helper class which can be used to pass useful parameters to functions.

Note that IAssetLoader can't store variables in class members, since there's
only one loader per application that can be used by multiple threads.
This class helps to pass parameters to loading functions.

@ingroup Loaders*/
class LoadingContext
{
public:

	RMLoaderAPI			Factory;
	ErrorsCollector		Warnings;
	AssetsVec			AssetsCollection;

protected:
public:
	explicit		LoadingContext		( RMLoaderAPI rm );
					~LoadingContext		() = default;

public:

	template< typename AssetType >
	void			CollectAsset		( ResourcePtr< AssetType > asset );

    /**@brief Collects asset if Nullable isn't exception.
    @return Returns true if asset was valid, false if it was exception.*/
    template< typename AssetType >
    bool			CollectAssetOrWarn	( const Nullable< ResourcePtr< AssetType > >& asset );

};


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline LoadingContext::LoadingContext		( RMLoaderAPI rm )
	:	Factory( rm )
{}


// ================================ //
//
template< typename AssetType >
inline void				LoadingContext::CollectAsset			( ResourcePtr< AssetType > asset )
{
	AssetsCollection.push_back( asset.Ptr() );
}

// ================================ //
//
template< typename AssetType >
inline bool             LoadingContext::CollectAssetOrWarn      ( const Nullable< ResourcePtr< AssetType > >& asset )
{
    if( Warnings.Success( asset ) )
    {
        AssetsCollection.push_back( asset.Get().Ptr() );
        return true;
    }

    // Sanity check.
    if( asset.Get() == nullptr )
    {
        std::string message = "Asset returned in Nullable shouldn't be nullptr. Asset type: [" + TypeID::get< AssetType >().get_name().to_string() + "].";
        Warnings.Add( InvalidCodeLogicException::Create( std::move( message ), __FILE__, __LINE__ ) );
    }

    return false;
}

}	// sw



