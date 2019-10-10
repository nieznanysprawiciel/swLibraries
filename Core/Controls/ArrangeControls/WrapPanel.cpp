/**
@file WrapPanel.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"



#include "WrapPanel.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::WrapPanel >( "sw::gui::WrapPanel" );
}



namespace sw {
namespace gui
{


WrapPanel::WrapPanel( UIElement* parent )
	: IPanel( parent )
{ }

WrapPanel::~WrapPanel()
{ }


}	// gui
}	// sw

