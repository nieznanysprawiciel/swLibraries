#pragma once
/**
@file Types.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <DirectXMath.h>


namespace sw
{

typedef DirectX::XMFLOAT2	Position2d;
typedef DirectX::XMFLOAT2	Size2d;
typedef DirectX::XMFLOAT2	Point2d;


/**@brief Rectangle structure.*/
struct Rect2d
{
	float			Left;
	float			Right;
	float			Top;
	float			Bottom;

public:
	float		GetWidth	() const { return Right - Left; }
	float		GetHeight	() const { return Top - Bottom; }

	bool		Intersects	( const Position2d& pos ) const
	{
		if( pos.x < Left )
			return false;
		if( pos.x > Right )
			return false;
		if( pos.y < Bottom )
			return false;
		if( pos.y > Top )
			return false;
		return true;
	}

	bool		Intersects( const Rect2d& other ) const;
};

inline Position2d operator+( Position2d left, Position2d right ) {
	return Position2d( left.x + right.x, left.y + right.y );
}

inline Position2d& operator+=( Position2d& left, Position2d right ) {
	left = left + right;
	return left;
}

namespace impl
{

// ================================ //
//
inline bool valueInRange( float value, float min, float max ) { return ( value >= min ) && ( value <= max ); }

}  // namespace

// ================================ //
// https://stackoverflow.com/a/306379

inline bool Rect2d::Intersects( const Rect2d& other ) const
{
    const Rect2d& A = *this;
    const Rect2d& B = other;

    bool xOverlap = impl::valueInRange( A.Left, B.Left, B.Left + B.GetWidth() )
                    || impl::valueInRange( B.Left, A.Left, A.Left + A.GetWidth() );

    bool yOverlap = impl::valueInRange( A.Top, B.Top, B.Top + B.GetHeight() )
                    || impl::valueInRange( B.Top, A.Top, A.Top + A.GetHeight() );

    return xOverlap && yOverlap;
}

}
