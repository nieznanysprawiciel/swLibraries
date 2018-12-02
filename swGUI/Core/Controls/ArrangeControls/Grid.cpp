/**
@file Grid.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "Grid.h"

RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::Grid >( "sw::gui::Grid" );
}





namespace sw {
namespace gui
{

/**@brief */
Grid::Grid( IControl* parent )
	:IPanel( parent )
{ }

/**@brief */
Grid::~Grid()
{ }

}	// gui
}	// sw


