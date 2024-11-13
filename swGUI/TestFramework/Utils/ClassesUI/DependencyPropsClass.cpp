#include "swGUI/TestFramework/stdafx.h"
#include "DependencyPropsClass.h"




// ================================ //
//
RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::DependencyPropsClass >( "sw::gui::DependencyPropsClass" )
		.property( "NumberItems", &sw::gui::DependencyPropsClass::GetNumberItems, &sw::gui::DependencyPropsClass::SetNumberItems )
		.property( "ContainerName", &sw::gui::DependencyPropsClass::GetContainerName, &sw::gui::DependencyPropsClass::SetContainerName )
        .property( "RandomName", &sw::gui::DependencyPropsClass::GetRandomName, &sw::gui::DependencyPropsClass::SetRandomName );
    ;
}




namespace sw {
namespace gui
{

DependencyProperty DependencyPropsClass::sNumberItemsProperty	= DependencyProperty::Register( "NumberItems", TypeID::get< DependencyPropsClass >() );
DependencyProperty DependencyPropsClass::sContainerNameProperty	= DependencyProperty::Register( "ContainerName", TypeID::get< DependencyPropsClass >() );
DependencyProperty DependencyPropsClass::sRandomNameProperty	= DependencyProperty::Register( "RandomName", TypeID::get< DependencyPropsClass >() );



// ================================ //
//
DependencyPropsClass::DependencyPropsClass()
	:	m_numberItems( 3 )
	,	m_containerName( "Name" )
	,	m_randomName( "Blaaa" )
{}


}	// gui
}	// sw