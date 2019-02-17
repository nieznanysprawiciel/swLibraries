#pragma once
/**
@file AssetLoadRequest.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/External/FastDelegate/FastDelegate.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/ResourceManager/IAssetLoadInfo.h"

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
	filesystem::Path		FilePath;
	IAssetLoadInfoPtr		LoadInfo;
	AsyncLoadHandler		OnLoaded;

private:
	bool					EndMessage;		///< Set to true if you want end loading thread execution.

// ================================ //
//
public:
	AssetLoadRequest()
		: EndMessage( false )
	{}

	AssetLoadRequest( const impl::CreateEndMessage& )
		: EndMessage( true )
	{}
	
	bool		IsEndMessage	() const			{ return EndMessage; }
};

}	// sw

