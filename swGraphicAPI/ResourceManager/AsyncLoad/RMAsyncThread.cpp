/**
@file RMAsyncThread.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/stdafx.h"


#include "RMAsyncThread.h"


namespace sw
{

// ================================ //
//
RMAsyncThread::RMAsyncThread	( ResourceManager* manager )
	:	m_resourceManager( manager )
	,	m_assetsThread( manager )		// This will start thread.
{}

// ================================ //
//
void				RMAsyncThread::LoadGenericAsync			( AssetPath assetName,
															  IAssetLoadInfoPtr desc,
															  TypeID type,
															  LoadingSuccessHandler onSuccess,
															  LoadingFailedHandler onFailed )
{
	AssetLoadRequest request;
	request.AssetPath = std::move( assetName );
	request.AssetType = type;
	request.LoadInfo = desc;
	request.OnLoaded = onSuccess;
	request.OnFailed = onFailed;

	m_assetsThread.QueueRequest( std::move( request ) );
}

}	// sw

