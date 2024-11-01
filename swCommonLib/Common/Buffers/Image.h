#pragma once
/**
@file Image.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"

#include "BufferTyped.h"


namespace sw
{

/**Represents buffer containing image.*/
template< typename ContentType, class Alloc = std::allocator< ContentType > >
class Image
{
private:
protected:

    BufferTyped< ContentType, Alloc >	m_buffer;
    uint32		                        m_width;
    uint32		                        m_height;

    /**Fallback Pixel returned in case access operation was attempted outside
    of image bounds. @ref Image class doesn't throw exception or cause access
    vioation in this case.*/
    ContentType                         m_fallback;

public:
    explicit Image( BufferTyped< ContentType >&& buffer, uint32 width, uint32 height )
        : m_buffer( std::move( buffer ) )
        , m_width( width )
        , m_height( height )
        , m_fallback( ContentType() )
    {
        assert( m_buffer.ElementsCount() == m_width * m_height );
    }

    explicit Image( uint32 width, uint32 height )
        : m_buffer( BufferTyped< ContentType >( width * height ) )
        , m_width( width )
        , m_height( height )
        , m_fallback( ContentType() )
    {}

    Image( const Image& image ) = default;
    Image( Image&& image ) = default;
	~Image() = default;

public:
    u32                 GetWidth        () const { return m_width; }
    u32                 GetHeight       () const { return m_height; }
    u8                  GetChannels     () const { return (u8)m_buffer.ElementSize(); }

    TypeID				GetType			() const { return m_buffer.GetType(); }
    Size				GetSize			() const { return m_buffer.GetSize(); }
    Size				ElementsCount	() const { return m_buffer.ElementsCount(); }
    Size				ElementSize		() const { return m_buffer.ElementSize(); }
    
    uint8*              GetRawData		() { return m_buffer.GetRawData(); }
    const uint8*        GetRawData		() const { return m_buffer.GetRawData(); }

    ContentType*        GetData		    () { return static_cast< ContentType* >( m_buffer.GetData() ); }
    const ContentType*  GetData		    () const { return static_cast< const ContentType* >( m_buffer.GetData() ); }

public:

    ContentType&        operator()      ( uint32 x, uint32 y );
    void				ZeroMemory      () { m_buffer.ZeroMemory(); }

    /**Checks if there was no write attempt outside of image bounds.*/
    bool                SanityCheck     () const { return m_fallback != ContentType(); }

public:
    /**@brief Takes ownership of memory buffer.*/
    BufferTyped< ContentType, Alloc >		Move			();
};

// ================================ //
//

template<typename ContentType, class Alloc>
inline ContentType&                     Image<ContentType, Alloc>::operator()( uint32 x, uint32 y )
{
    if( x >= m_width || y >= m_height )
        return m_fallback;
    return m_buffer[ y * m_width + x ];
}

// ================================ //
//

template<typename ContentType, class Alloc >
inline BufferTyped<ContentType, Alloc>  Image<ContentType, Alloc>::Move()
{
    return std::move( this->m_buffer );
}

}
