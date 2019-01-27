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
	explicit		GradientBrush		() = default;
	virtual			~GradientBrush		() = default;


	virtual std::wstring		ConstantsName		();
	virtual std::wstring		TextureSource		() override;

public:

	void						AddGradientStop		( GradientStop stop );
	void						RemoveGradientStop	( Size idx );

protected:

	BufferRange					PrepareBuffer		( BufferRange constants );

	virtual Size				ConstantsSize		() const = 0;

private:

	Size						ExpectedBufferSize	() const;
	Size						GradientStopsSize	() const;

	void						ReallocateBuffer	( Size newSize );
	void						FillBufferContent	( BufferRange constants );
};


}	// gui
}	// sw

