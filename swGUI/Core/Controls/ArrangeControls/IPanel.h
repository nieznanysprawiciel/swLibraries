#pragma once

#include "swGUI/Core/Controls/UIElement.h"



namespace sw {
namespace gui
{

/**@brief */
class IPanel : public UIElement
{
	RTTR_ENABLE( UIElement )
	RTTR_REGISTRATION_FRIEND
private:
protected:
public:
	IPanel		( UIElement* parent );
	virtual			~IPanel		();

};



}	// gui
}	// sw

