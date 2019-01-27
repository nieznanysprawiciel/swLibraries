#pragma once
/**
@file LinearGradientBrush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "GradientBrush.h"

#include "swCommonLib/Common/Buffers/StackBuffer.h"
#include "swGUI/Core/System/CommonTypes/CommonTypes.h"



namespace sw {
namespace gui
{


/**@brief Draws linear gradient on @ref Geometry.
@ingroup Brushes*/
class LinearGradient : public GradientBrush
{
	RTTR_ENABLE( GradientBrush );
	RTTR_REGISTRATION_FRIEND;
public:

	struct Constants
	{
		Point		GradientStart;
		Point		GradientEnd;
	};

private:
protected:

	StackBuffer< Constants >		m_constants;

public:
	explicit		LinearGradient		();
	virtual			~LinearGradient		() = default;


	virtual	BufferRange		BufferData			() override;
	virtual std::string		ShaderFunctionFile	() override;

protected:

	virtual Size				ConstantsSize		() const override;
};

DEFINE_PTR_TYPE( LinearGradient );


}	// gui
}	// sw

