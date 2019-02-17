#pragma once
/**
@file LoadBarrier.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/System/Path.h"
#include "swCommonLib/Common/TypesDefinitions.h"

#include <set>
#include <atomic>
#include <condition_variable>


namespace sw
{

/**@brief Class describing asset waiting for beeing loaded.*/
class WaitingAsset
{
	friend class LoadBarrier;
private:

	filesystem::Path			m_fileName;
	std::atomic< uint16	>		m_numWaiting;
	bool						m_ready;

	std::condition_variable		m_condition;
	std::mutex					m_lock;

public:
	WaitingAsset		() = default;
	WaitingAsset		( const filesystem::Path& filePath );
	~WaitingAsset		();


private:

	/**@brief Function blocks until resource will be loaded.
	@return Returns true if it was last waiting thread.*/
	bool				WaitUntilLoaded		();

	/**@brief Increments loading threads count.*/
	void				RequestAsset		();

	/**@brief Notify all threads waiting for this asset.
	@return Returns true if it was last waiting thread.*/
	bool				LoadingCompleted	();

	/**@brief Check if file is during laoding.*/
	bool				Compare				( const filesystem::Path& filePath );


private:
	FRIEND_CLASS_TESTER( LoadBarrier )
};



/**@brief Class prevents ResourceManager from loading Assets multiple times.*/
class LoadBarrier
{
private:

	std::vector< WaitingAsset* >	m_waitingAssets;
	std::mutex						m_lock;

public:
	~LoadBarrier();

	/**@brief Tries to access asset described by filePath. If asset exists, function increments waiting threads counter.
	Otherwise new WaitingAsset object is created to block future loads.
	@return Function returns true if asset already existed. If WaitingAsset was created in this function call function returns true.
	Note: WaitingAsset should never be nullptr.*/
	std::pair< WaitingAsset*, bool >		RequestAsset		( const filesystem::Path& filePath );

	/**@brief Function waits until asset will be loaded.*/
	void									WaitUntilLoaded		( WaitingAsset* asset );

	/**@brief Notify all threads waiting for this asset.*/
	void									LoadingCompleted	( const filesystem::Path& filePath );

private:

    bool                                    RemoveWaitingAsset	( WaitingAsset* asset );

private:
	FRIEND_CLASS_TESTER( LoadBarrier )
};


}	// sw

