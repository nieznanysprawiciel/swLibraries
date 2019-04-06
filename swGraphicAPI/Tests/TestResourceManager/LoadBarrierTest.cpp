#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/Multithreading/ThreadsBarrier.h"

#include "swGraphicAPI/ResourceManager/AsyncLoad/LoadBarrier.h"




namespace sw
{

// ================================ //
//
class CLASS_TESTER( LoadBarrier )
{
private:
public:

	static std::vector< WaitingAsset* > &       GetWaitingAssets    ( LoadBarrier & barrier ) { return barrier.m_waitingAssets; }

};


}	// sw


const int numThreads = 4;

sw::ThreadsBarrier		gPreAccessBarrier( numThreads );
sw::ThreadsBarrier		gPreWaitBarrier( numThreads - 1 );
sw::LoadBarrier			gLoadBarrier;
std::vector< int >		gOrderChecker;
std::mutex				gCheckerLock;

filesystem::Path assetFile( "assets/wombat.jpg" );
filesystem::Path independentAsset( "assets/texture.jpg" );

bool threadsInternalResult[ numThreads ];
bool notNullWaitingAsset[ numThreads ];



// ================================ //
//
void		PushThreadNum		( int threadNum )
{
	gCheckerLock.lock();
	gOrderChecker.push_back( threadNum );
	gCheckerLock.unlock();
}


// ================================ //
//
void		FakeLoadAsset		( int threadNum )
{
	PushThreadNum( threadNum );

	gPreWaitBarrier.ArriveAndWait();

	std::this_thread::sleep_for( std::chrono::milliseconds( 13 ) );

	PushThreadNum( threadNum );

	gLoadBarrier.LoadingCompleted( assetFile );
}

// ================================ //
//
void		LoadingThread		( int threadNum )
{
	auto result = gLoadBarrier.RequestAsset( assetFile );

	// Allow other threads to call RequestAsset.
	gPreAccessBarrier.ArriveAndWait();
	
	threadsInternalResult[ threadNum ] = result.second;
	notNullWaitingAsset[ threadNum ] = result.first != nullptr;
	
	FakeLoadAsset( threadNum );
}

// ================================ //
//
void		RequestingThread	( int threadNum )
{
	// LoadingThread must RequestAsset first. Wait for it.
	gPreAccessBarrier.ArriveAndWait();

	auto result = gLoadBarrier.RequestAsset( assetFile );

	threadsInternalResult[ threadNum ] = result.second;
	notNullWaitingAsset[ threadNum ] = result.first != nullptr;

	gPreWaitBarrier.ArriveAndWait();
	gLoadBarrier.WaitUntilLoaded( result.first );
	
	PushThreadNum( threadNum );
}

// ================================ //
//
void		IndependentAssetThread	( int threadNum )
{
	// LoadingThread must RequestAsset first. Wait for it.
	gPreAccessBarrier.ArriveAndWait();

	auto result = gLoadBarrier.RequestAsset( independentAsset );

	// Independent thread should pass without blocking. result.second should be false.
	threadsInternalResult[ threadNum ] = result.second;
	notNullWaitingAsset[ threadNum ] = result.first != nullptr;

	gLoadBarrier.LoadingCompleted( independentAsset );
}


// ================================ //
// Only one thread should enter loading at the same time. Rest should wait.
TEST_CASE( "GraphicAPI.LoadBarrier.MultiThreadsLoading", "[GraphicAPI]" )
{
	std::thread threads[ numThreads ];

	threads[ 0 ] = std::thread( &LoadingThread, 0 );
	for( int i = 1; i < numThreads - 1; ++i )
		threads[ i ] = std::thread( &RequestingThread, i );

	// Independent thread
	threads[ numThreads - 1 ] = std::thread( &IndependentAssetThread, numThreads - 1 );

	for( auto& thread : threads )
		thread.join();


	// Waiting asset should never be nullptr.
	for( auto notNull : notNullWaitingAsset )
		CHECK( notNull == true );

	CHECK( threadsInternalResult[ 0 ] == false );
	CHECK( threadsInternalResult[ 1 ] == true );
	CHECK( threadsInternalResult[ 2 ] == true );
	CHECK( threadsInternalResult[ 3 ] == false );

	REQUIRE( gOrderChecker.size() == 4 );

	CHECK( gOrderChecker[ 0 ] == 0 );
	CHECK( gOrderChecker[ 1 ] == 0 );
	CHECK( ( gOrderChecker[ 2 ] == 1 || gOrderChecker[ 2 ] == 2 ) );
	CHECK( ( gOrderChecker[ 3 ] == 1 || gOrderChecker[ 3 ] == 2 ) );

    // Waiting assets list should be cleaned.
    CHECK( sw::CLASS_TESTER( LoadBarrier )::GetWaitingAssets( gLoadBarrier ).size() == 0 );
}


sw::LoadBarrier     gBarrier;


// ================================ //
// Load asset from single thread. Barrier should end in clean state without waiting assets on list.
// Note that this checks state cleaning in situation, when there're no other threads what differs
// from previous test case.
TEST_CASE( "GraphicAPI.LoadBarrier.SingleAssetLoading", "[GraphicAPI]" )
{
    auto result = gBarrier.RequestAsset( assetFile );

    // New Waiting asset should be created in this case.
    REQUIRE( result.second == false );
    CHECK( result.first != nullptr );

    // Here in real application should be loading code.

    gBarrier.LoadingCompleted( assetFile );

    // Waiting assets list should be cleaned.
    CHECK( sw::CLASS_TESTER( LoadBarrier )::GetWaitingAssets( gBarrier ).size() == 0 );
}

// ================================ //
//
TEST_CASE( "GraphicAPI.LoadBarrier.SingleAssetLoading.FailedLoading", "[GraphicAPI]" )
{
	sw::LoadBarrier     barrier;
    auto result = barrier.RequestAsset( assetFile );

    // New Waiting asset should be created in this case.
    REQUIRE( result.second == false );
    CHECK( result.first != nullptr );

    // Here in real application should be loading code.

    barrier.LoadingFailed( assetFile, std::make_shared< sw::RuntimeException >( "Error!" ) );

    // Waiting assets list should be cleaned.
    CHECK( sw::CLASS_TESTER( LoadBarrier )::GetWaitingAssets( barrier ).size() == 0 );
}


// ================================ //
// Checks if we can access error after loading asset.
TEST_CASE( "GraphicAPI.LoadBarrier.SingleAssetLoading.FailedLoading.AccessError", "[GraphicAPI]" )
{
	sw::ThreadsBarrier	waitForMainThread( 2 );
	sw::ThreadsBarrier	waitWithLoading( 2 );

	sw::LoadBarrier     waitingAssets;

	std::thread loadingThread( [&]()
	{
		auto result = waitingAssets.RequestAsset( assetFile );

		waitForMainThread.ArriveAndWait();		// This forces this thread to request asset as first.
		waitWithLoading.ArriveAndWait();		// Wait for first thread to request asset.

		waitingAssets.LoadingFailed( assetFile, std::make_shared< sw::RuntimeException >( "Error!" ) );
	} );

	// Wait for second thread to RequestAsset
	waitForMainThread.ArriveAndWait();

	// Request asset as second.
	auto result = waitingAssets.RequestAsset( assetFile );

	sw::WaitingAsset* assetWait = result.first;
	bool needWait = result.second;

	REQUIRE( needWait );		// Needs to wait.

	// After this barrier second thread can send LoadingFailed
	waitWithLoading.ArriveAndWait();

	auto loadingResult = waitingAssets.WaitUntilLoaded( assetWait );

	loadingThread.join();

	REQUIRE( loadingResult.IsValid() == false );
	CHECK( loadingResult.GetError() != nullptr );

    // Waiting assets list should be cleaned.
    CHECK( sw::CLASS_TESTER( LoadBarrier )::GetWaitingAssets( waitingAssets ).size() == 0 );
}
