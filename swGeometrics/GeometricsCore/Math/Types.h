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
	float		GetWidth	() { return Right - Left; }
	float		GetHeight	() { return Top - Bottom; }

	bool		Intersects	( const Position2d& pos )
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
};

inline Position2d operator+( Position2d left, Position2d right ) {
	return Position2d( left.x + right.x, left.y + right.y );
}

inline Position2d& operator+=( Position2d& left, Position2d right ) {
	left = left + right;
	return left;
}

}
