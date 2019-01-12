#pragma once
/**
@file SolidColorBrush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "Brush.h"

#include "swCommonLib/Common/Buffers/StackBuffer.h"
#include "swGUI/Core/System/CommonTypes/CommonTypes.h"


namespace sw {
namespace gui
{




/**@brief Draws geometry with solid color.
@ingroup Brushes*/
class SolidColorBrush : public Brush
{
	RTTR_ENABLE( Brush );
	RTTR_REGISTRATION_FRIEND
protected:

	struct Constants
	{
		Color		Color;
	};

protected:

	StackBuffer< Constants >		m_constants;

public:
	explicit		SolidColorBrush		();
	explicit		SolidColorBrush		( const Color& color );
					~SolidColorBrush	() = default;

	void			SetColor			( const Color& color )		{ m_constants.Color = color; }
	Color			GetColor			() const					{ return m_constants.Color; }

public:

	virtual BufferRange			BufferData			() override;
	virtual std::string			ShaderFunctionFile	() override;
	virtual std::wstring		TextureSource		() override;
	virtual std::wstring		ConstantsName		() override;
};

DEFINE_PTR_TYPE( SolidColorBrush );


}	// gui
}	// sw




