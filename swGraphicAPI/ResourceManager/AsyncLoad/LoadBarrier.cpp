/**
@file LoadBarrier.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"
#include "LoadBarrier.h"


namespace sw
{

// ================================ //
//
WaitingAsset::WaitingAsset	( const filesystem::Path& filePath )
	:	m_fileName( filePath )
	,	m_numWaiting( 0 )
	,	m_ready( false )
{}

// ================================ //
//
WaitingAsset::~WaitingAsset()
{
	// @todo It won't work :(
	LoadingCompleted();
}

// ================================ //
//
bool			WaitingAsset::WaitUntilLoaded		()
{
	std::unique_lock< std::mutex > lock( m_lock );
	while( !m_ready )
		m_condition.wait( lock );
	
	lock.unlock();

	auto remaining = --m_numWaiting;
	if( remaining == 0 )
		return true;
	return false;
}

// ================================ //
//
void			WaitingAsset::RequestAsset			()
{
	m_numWaiting++;
}

// ================================ //
//
bool			WaitingAsset::LoadingCompleted		()
{
	return LoadingCompleted( nullptr );
}

// ================================ //
//
bool			WaitingAsset::LoadingCompleted		( ExceptionPtr error )
{
    m_lock.lock();

    m_ready = true;
	m_error = error;
    bool noOneWaits = m_numWaiting == 0;

    m_lock.unlock();

    m_condition.notify_all();

    if( noOneWaits )
        return true;
    return false;
}

// ================================ //
//
bool			WaitingAsset::Compare				( const filesystem::Path& filePath )
{
	return m_fileName == filePath;
}


//====================================================================================//
//				LoadBarrier
//====================================================================================//

// ================================ //
//
LoadBarrier::~LoadBarrier()
{
	for( auto& asset : m_waitingAssets )
		delete asset;
}

// ================================ //
//
std::pair< WaitingAsset*, bool >		LoadBarrier::RequestAsset		( const filesystem::Path& filePath )
{
	std::unique_lock< std::mutex > lock( m_lock );

	WaitingAsset* assetWait = nullptr;
	for( auto asset : m_waitingAssets )
	{
		if( asset->Compare( filePath ) )
		{
			assert( assetWait == nullptr );		// Should be only one file in waiting vector.
			assetWait = asset;
		}
	}

	if( assetWait )
	{
		assetWait->RequestAsset();
		return std::make_pair< WaitingAsset*, bool >( std::move( assetWait ), true );
	}
	else
	{
		auto iter = m_waitingAssets.insert( m_waitingAssets.end(), new WaitingAsset( filePath ) );
		return std::make_pair< WaitingAsset*, bool >( std::move( *iter ), false );
	}
}

// ================================ //
//
ReturnResult							LoadBarrier::WaitUntilLoaded	( WaitingAsset* asset )
{
	bool isLast = asset->WaitUntilLoaded();
	auto error = asset->GetError();

	if( isLast )
	{
		std::unique_lock< std::mutex > lock( m_lock );
        bool removed = RemoveWaitingAsset( asset );

		assert( removed );
	}

	if( error != nullptr )
		return error;
	else
		return Success::True;
}

// ================================ //
//
void									LoadBarrier::LoadingCompleted	( const filesystem::Path& filePath )
{
	LoadingFinishedImpl( filePath, nullptr );
}

// ================================ //
//
void									LoadBarrier::LoadingFailed		( const filesystem::Path& filePath, ExceptionPtr error )
{
	LoadingFinishedImpl( filePath, error );
}

// ================================ //
//
void									LoadBarrier::LoadingFinishedImpl( const filesystem::Path& filePath, ExceptionPtr error )
{
    std::unique_lock< std::mutex > lock( m_lock );

    WaitingAsset* asset = nullptr;

    for( int i = 0; i < m_waitingAssets.size(); ++i )
    {
        if( m_waitingAssets[ i ]->Compare( filePath ) )
        {
            asset = m_waitingAssets[ i ];
            break;
        }
    }

    
    if( asset )
    {
        bool noOneWaits = asset->LoadingCompleted( error );		// Error can be nullptr and that means that asset was loaded successfully.

        // Remove if there're no waiting threads
        if( noOneWaits )
            RemoveWaitingAsset( asset );

        // In other cases WaitingAsset will be removed when last thread will leave waiting lock.
    }
}

// ================================ //
//
bool                                    LoadBarrier::RemoveWaitingAsset ( WaitingAsset* asset )
{
    bool removed = false;
    for( auto iter = m_waitingAssets.begin(); iter != m_waitingAssets.end(); ++iter )
    {
        if( *iter == asset )
        {
            delete *iter;
            m_waitingAssets.erase( iter );
            removed = true;
            break;
        }
    }

    return removed;
}

}	// sw

