/**
@file IPanel.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "IPanel.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::IPanel >( "sw::gui::IPanel" );
}



namespace sw {
namespace gui
{


IPanel::IPanel( UIElement* parent )
	: UIElement( parent )
{ }

IPanel::~IPanel()
{ }


}	// gui
}	// sw

