#pragma once
/**
@file ImageRegion.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/fmt.h"

#include "Image.h"


namespace sw
{

/**Region of an image represented as top left point and dimmension of the rectangle.*/
struct ImageRect
{
    uint32		X;
    uint32		Y;
    uint32		Width;
    uint32		Height;

public:
    bool        Intersects      ( const ImageRect& other ) const;
};



/**@brief Represents region of an image and implements basic operations.
This class doesn't own the data.*/
template< typename ContentType, class Alloc = std::allocator< ContentType > >
class ImageRegion
{
private:
protected:

    Image< ContentType, Alloc >& m_image;
    ImageRect                       m_region;

    /**Fallback Pixel returned in case access operation was attempted outside
    of image bounds. @ref Image class doesn't throw exception or cause access
    vioation in this case.*/
    ContentType                         m_fallback;

protected:
    explicit ImageRegion( Image< ContentType, Alloc >& image, ImageRect region )
        : m_image( image )
        , m_region( region )
    {
        assert( m_image.GetHeight() >= region.Y + region.Height );
        assert( m_image.GetWidth() >= region.X + region.Width );
    }

public:
    ImageRegion( const ImageRegion& image ) = default;
    ImageRegion( ImageRegion&& image ) = default;
    ~ImageRegion() = default;

    /**Creates ImageRegion from Image in a safe way.*/
    static Nullable< ImageRegion< ContentType, Alloc > >   From( Image< ContentType, Alloc >& image, ImageRect region );

public:
    u32                 GetOriginalImageWidth       () const { return m_image.GetWidth(); }
    u32                 GetOriginalImageHeight      () const { return m_image.GetHeight(); }
    u32                 GetWidth        () const { return m_region.Width; }
    u32                 GetHeight       () const { return m_region.Height; }
    u8                  GetChannels     () const { return (u8)m_image.ElementSize(); }

    TypeID				GetType			() const { return m_image.GetType(); }
    Size				GetSize			() const { return m_image.GetSize(); }
    Size				ElementsCount	() const { return m_image.ElementsCount(); }
    Size				ElementSize		() const { return m_image.ElementSize(); }

public:

    /**Access pixel at given position inside the region.
    Function translates coordinates to full image space.

    Attempt to access pixel outside of region will fail silently, but won't crash.
    Such an attempt can be considered as no operation.*/
    ContentType& operator()      ( uint32 x, uint32 y );

    /**Checks if there was no write attempt outside of image  region bounds.*/
    bool                SanityCheck     () const { return m_fallback != ContentType(); }
};


/**Creates ImageRegion from Image in a safe way.*/
template<typename ContentType, class Alloc>
inline Nullable<ImageRegion<ContentType, Alloc>>    ImageRegion<ContentType, Alloc>::From( Image<ContentType, Alloc>& image, ImageRect region )
{
    if( region.X + region.Width > image.GetWidth() )
        return std::make_shared< RuntimeException > ( fmt::format( "Region width outside of original image bounds." ) );

    if( region.Y + region.Height > image.GetHeight() )
        return std::make_shared< RuntimeException > ( fmt::format( "Region height outside of original image bounds." ) );

    return ImageRegion< ContentType, Alloc >( image, region );
}

// ================================ //
//

template<typename ContentType, class Alloc>
inline ContentType& ImageRegion<ContentType, Alloc>::operator()( uint32 x, uint32 y )
{
    if( x >= m_region.Width || y >= m_region.Height )
        return m_fallback;

    return m_image( x + m_region.X, y + m_region.Y );
}

namespace
{

// ================================ //
//
inline bool valueInRange( int value, int min, int max )
{
    return (value >= min) && (value <= max);
}

}

// ================================ //
// https://stackoverflow.com/a/306379

inline bool            ImageRect::Intersects( const ImageRect& other ) const
{
    const ImageRect& A = *this;
    const ImageRect& B = other;

    bool xOverlap = valueInRange( A.X, B.X, B.X + B.Width ) ||
        valueInRange( B.X, A.X, A.X + A.Width );

    bool yOverlap = valueInRange( A.Y, B.Y, B.Y + B.Height ) ||
        valueInRange( B.Y, A.Y, A.Y + A.Height);

    return xOverlap && yOverlap;
}

}	// sw
