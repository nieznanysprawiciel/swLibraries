#pragma once
/**
@file AngleGradientBrush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "GradientBrush.h"

#include "swCommonLib/Common/Buffers/StackBuffer.h"
#include "swCommonLib/System/Path.h"
#include "swGUI/Core/System/CommonTypes/CommonTypes.h"



namespace sw {
namespace gui
{


/**@brief Draws angle gradient on @ref Geometry.
@ingroup Brushes*/
class AngleGradientBrush : public GradientBrush
{
    RTTR_ENABLE( GradientBrush );
    RTTR_REGISTRATION_FRIEND;
public:

    struct Constants
    {
        Point		GradientCenter;
    };

private:
protected:

    StackBuffer< Constants >		m_constants;

public:
    explicit		AngleGradientBrush			();
    virtual			~AngleGradientBrush		    () = default;


    virtual	BufferRange		    BufferData			() override;
    virtual filesystem::Path	ShaderFunctionFile	() override;

    void					    SetGradientCenter	( Point center );

protected:

    virtual Size				ConstantsSize		() const override;
};

DEFINE_PTR_TYPE( AngleGradientBrush );


}	// gui
}	// sw

