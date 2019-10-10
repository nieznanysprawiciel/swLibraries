#pragma once
/**
@file AssetLoadRequest.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/External/FastDelegate/FastDelegate.h"

#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"

#include "AssetLoadResponse.h"


namespace sw
{

class AssetsThread;


namespace impl
{

class CreateEndMessage
{	
	friend class AssetsThread;
	CreateEndMessage() {}
};

}



/**@brief Queue element for asynchronous asset loading thread.

@ingroup AsyncLoading*/
struct AssetLoadRequest
{
	AssetPath				AssetPath;
	TypeID					AssetType;
	IAssetLoadInfoPtr		LoadInfo;
	LoadingSuccessHandler	OnLoaded;
	LoadingFailedHandler	OnFailed;

private:
	bool					EndMessage;		///< Set to true if you want end loading thread execution.

// ================================ //
//
public:
	AssetLoadRequest()
		:	EndMessage( false )
		,	AssetType( TypeID::get_by_name( "" ) )	// Set invalid type.
	{}

	AssetLoadRequest( const impl::CreateEndMessage& )
		:	EndMessage( true )
		,	AssetType( TypeID::get_by_name( "" ) )	// Set invalid type.
	{}
	
	bool		IsEndMessage	() const			{ return EndMessage; }
};

}	// sw

