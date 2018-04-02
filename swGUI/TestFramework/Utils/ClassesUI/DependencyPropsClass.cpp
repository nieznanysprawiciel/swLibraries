#include "swGUI/TestFramework/stdafx.h"
#include "DependencyPropsClass.h"




// ================================ //
//
RTTR_REGISTRATION
{
	rttr::registration::class_< sw::gui::DependencyPropsClass >( "sw::gui::DependencyPropsClass" )
		.property( "NumberItems", &sw::gui::DependencyPropsClass::GetNumberItems, &sw::gui::DependencyPropsClass::SetNumberItems )
		.property( "ContainerName", &sw::gui::DependencyPropsClass::GetContainerName, &sw::gui::DependencyPropsClass::SetContainerName );
}




namespace sw {
namespace gui
{

DependencyProperty DependencyPropsClass::sNumberItemsProperty	= DependencyProperty::Register( "NumberItems", TypeID::get< DependencyPropsClass >() );
DependencyProperty DependencyPropsClass::sContainerNameProperty	= DependencyProperty::Register( "ContainerName", TypeID::get< DependencyPropsClass >() );



// ================================ //
//
DependencyPropsClass::DependencyPropsClass()
	:	m_numberItems( 3 )
	,	m_containerName( "Name" )
{}


}	// gui
}	// sw