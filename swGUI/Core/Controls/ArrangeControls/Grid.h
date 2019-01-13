#pragma once

#include "IPanel.h"


namespace sw {
namespace gui
{

/**@brief */
class Grid : public IPanel
{
	RTTR_ENABLE( IPanel )
		RTTR_REGISTRATION_FRIEND
private:
protected:
public:
	explicit	Grid	( UIElement* parent );
	virtual		~Grid	();

};


}	// gui
}	// sw
