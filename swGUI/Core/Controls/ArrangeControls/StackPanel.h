#pragma once

#include "IPanel.h"


namespace sw {
namespace gui
{

/**@brief */
class StackPanel : public IPanel
{
	RTTR_ENABLE( IPanel )
private:
protected:
public:
	explicit	StackPanel		( UIElement* parent );
	virtual		~StackPanel		();

};


}	// gui
}	// sw

