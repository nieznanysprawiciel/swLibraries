/**
@file DockPanel.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "DockPanel.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::DockPanel >( "sw::gui::DockPanel" );
}



namespace sw {
namespace gui
{


DockPanel::DockPanel( IControl* parent )
	: IPanel( parent )
{ }

DockPanel::~DockPanel()
{ }


}	// gui
}	// sw

