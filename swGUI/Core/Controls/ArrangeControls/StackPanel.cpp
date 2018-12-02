/**
@file StackPanel.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "StackPanel.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::StackPanel >( "sw::gui::StackPanel" );
}

namespace sw {
namespace gui
{




StackPanel::StackPanel( IControl* parent )
	: IPanel( parent )
{ }

StackPanel::~StackPanel()
{ }


}	// gui
}	// sw

