#pragma once
/**
@file GradientBrush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "Brush.h"

#include "swCommonLib/Common/Buffers/BufferRaw.h"

#include <vector>



namespace sw {
namespace gui
{

/**@brief Gradient point.
@ingroup Brushes*/
struct GradientStop
{
	uint32		Color;
	float		Offset;

// ================================ //
//
	GradientStop() {}

	GradientStop( uint32 color, float offset )
		:	Color( color )
		,	Offset( offset )
	{}
};



/**@brief Base class for gradients.
@ingroup Brushes*/
class GradientBrush : public Brush
{
private:
protected:

	std::vector< GradientStop >		m_gradientStops;
	BufferRaw						m_buffer;

public:
	explicit		GradientBrush		( Size constantsSize );
	virtual			~GradientBrush		() = default;


	virtual std::wstring		ConstantsName		();
	virtual std::wstring		TextureSource		() override;

public:

	void						AddGradientStop		( GradientStop stop );
	void						RemoveGradientStop	( Size idx );

	const std::vector< GradientStop >&		GetGradintStops		() const { return m_gradientStops; }

protected:

	BufferRange					PrepareBuffer		( BufferRange constants );

	virtual Size				ConstantsSize		() const = 0;

private:

	Size						ExpectedBufferSize	() const;
	Size						ExpectedBufferSize	( Size constantsSize ) const;
	Size						GradientStopsSize	() const;

	void						ReallocateBuffer	( Size newSize );
	void						FillBufferContent	( BufferRange constants );
};


}	// gui
}	// sw

