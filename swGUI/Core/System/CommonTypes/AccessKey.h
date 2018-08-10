#pragma once
/**
@file AccessKey.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


namespace sw {
namespace gui
{

/**@brief Class Restricts access to some functions only for chosen classes.*/
class AccessKey
{
	friend class GUISystem;
	friend class EventsSystem;
private:
	AccessKey() = default;					///< Only friend class can create object.
	AccessKey( const AccessKey& ) {}		///< Only friend class can create object.
	AccessKey( const AccessKey&& ) {}		///< Only friend class can create object.
public:
};

}	// gui
}	// sw