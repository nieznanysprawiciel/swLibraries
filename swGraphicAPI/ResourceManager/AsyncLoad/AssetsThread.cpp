/**
@file AssetsThread.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "AssetsThread.h"


namespace sw
{


// ================================ //
//
AssetsThread::AssetsThread( ResourceManager* resourceManApi )
	:	m_resourceManager( resourceManApi )
{
	m_thread = std::thread( &AssetsThread::LoadingThread, this );
}

// ================================ //
//
AssetsThread::~AssetsThread()
{
	StopThread();

	m_thread.join();
}

// ================================ //
//
void			AssetsThread::StopThread		()
{
	/// @todo Maybe we should empty queue.
	m_requests.Push( AssetLoadRequest( impl::CreateEndMessage() ) );
}

// ================================ //
//
void			AssetsThread::QueueRequest		( AssetLoadRequest&& request )
{
	m_requests.Push( request );
}

// ================================ //
//
void			AssetsThread::LoadingThread		()
{
	AssetLoadRequest request;

	while( true )
	{
		m_requests.Pop( request );
		
		if( request.IsEndMessage() )
			break;

		auto result = m_resourceManager->LoadGeneric( request.AssetPath, request.LoadInfo.get(), request.AssetType );

		AssetLoadResponse response;
		response.FilePath = std::move( request.AssetPath );
		response.LoadInfo = std::move( request.LoadInfo );

		if( result.IsValid() )
		{
			response.Resource = result.Get();

			if( request.OnLoaded )
				request.OnLoaded( response );
		}
		else
		{
			response.Resource = nullptr;

			if( request.OnFailed )
				request.OnFailed( response, result.GetError() );
		}
	}
}

}	// sw

