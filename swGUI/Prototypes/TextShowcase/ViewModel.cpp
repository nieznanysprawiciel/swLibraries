/**
@file ViewModel.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Application.h"


RTTR_REGISTRATION
{
    rttr::registration::class_< ViewModel >( "ViewModel" )
        .property( "TimeCounter", &ViewModel::GetTimeCounter, &ViewModel::SetTimeCounter );
}


using namespace sw::gui;


DependencyProperty ViewModel::sTimeCounter = DependencyProperty::Register( "TimeCounter", TypeID::get< ViewModel >() );
