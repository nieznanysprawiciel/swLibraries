#pragma once
/**
@file UpdateTracker.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <type_traits>
#include <limits>


namespace sw {
namespace gui
{

template< typename CounterType > class UpdateCounter;

/**@brief Tracks if Resource should be updated. Enables lazy re-loading and updating
of Resources.

UpdateCounter is used to invalidate Resource.
UpdateTracker stores the last update number.*/
template< typename CounterType > class UpdateTracker
{
    friend class UpdateCounter< CounterType >;

protected:
    CounterType m_updateCounter;

public:
    explicit UpdateTracker()
        : m_updateCounter( 0 )
    {
        static_assert( std::numeric_limits< CounterType >::is_integer, "UpdateTracker type must be integer type." );
        static_assert( !std::numeric_limits< CounterType >::is_signed, "UpdateTracker type must be unsigned." );
    }
    UpdateTracker( const UpdateTracker& tracker ) = delete;

    void Synchronize( const UpdateCounter< CounterType >& counter ) { m_updateCounter = counter.m_updateCounter; }
};

/**@brief Check @ref UpdateTracker*/
template< typename CounterType > class UpdateCounter : public UpdateTracker< CounterType >
{
public:
    void Invalidate() { m_updateCounter++; }
    bool NeedsUpdate( const UpdateTracker< CounterType >& tracker ) const;
    bool NeedsUpdateAndSync( UpdateTracker< CounterType >& tracker ) const;

    using UpdateTracker::UpdateTracker;
private:
    using UpdateTracker::Synchronize;
    UpdateCounter( const UpdateCounter& counter ) = delete;
};

typedef UpdateCounter< uint16 > UpdateCounter16;
typedef UpdateTracker< uint16 > UpdateTracker16;
typedef UpdateCounter< uint32 > UpdateCounter32;
typedef UpdateTracker< uint32 > UpdateTracker32;
typedef UpdateCounter< uint64 > UpdateCounter64;
typedef UpdateTracker< uint64 > UpdateTracker64;


// ================================ //

template< typename CounterType >
inline bool UpdateCounter< CounterType >::NeedsUpdate( const UpdateTracker< CounterType >& tracker ) const
{
    // Tracker's counter should be always lower or equal to this counter.
    // If it's not the case, then most probably counter has overflown
    // and Tracker missed the update in one of previous frames.
    // In this case the Resource should be updated.
    // The chance of missing the update is very low equal to 1 / sizeof( CounterType ).
    if( m_updateCounter < tracker.m_updateCounter )
        return true;

    return m_updateCounter > tracker.m_updateCounter;
}

// ================================ //

template< typename CounterType >
inline bool UpdateCounter< CounterType >::NeedsUpdateAndSync( UpdateTracker< CounterType >& tracker ) const
{
    bool needsUpdate = NeedsUpdate( tracker );
    tracker.Synchronize( *this );
    return needsUpdate;
}

}  // namespace gui
}  // sw
