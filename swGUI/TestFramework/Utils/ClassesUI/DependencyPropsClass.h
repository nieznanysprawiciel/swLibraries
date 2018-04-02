#pragma once
/**
@file DependencyPropsClass.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGUI/Core/System/DataBinding/DependencyObject.h"




namespace sw {
namespace gui
{


// ================================ //
//
class DependencyPropsClass : public DependencyObject
{
	RTTR_ENABLE( DependencyObject )
	RTTR_REGISTRATION_FRIEND
public:

	static DependencyProperty sNumberItemsProperty;
	static DependencyProperty sContainerNameProperty;

private:

	uint32			m_numberItems;
	std::string		m_containerName;

public:

	explicit		DependencyPropsClass	();


public:

	uint32					GetNumberItems			() const { return m_numberItems; }
	void					SetNumberItems			( uint32 value ) { DependencyObject::SetValue( sNumberItemsProperty, value, &DependencyPropsClass::m_numberItems ); }

	const std::string&		GetContainerName		() const { return m_containerName; }
	void					SetContainerName		( const std::string& value ) { DependencyObject::SetValue( sContainerNameProperty, value, &DependencyPropsClass::m_containerName ); }
};



}	// gui
}	// sw
