#pragma once
/**
@file StringContainer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Object.h"



namespace sw
{


// ================================ //
//
class StringContainer : public Object
{
	RTTR_ENABLE( Object )
	RTTR_REGISTRATION_FRIEND
public:

	std::string			Description;
	std::wstring		Content;

protected:
public:
	explicit		StringContainer		();
	~StringContainer	() = default;

	void			StringsSet2			();
};


// ================================ //
//
inline StringContainer::StringContainer()
	:	Description( "Description of Field")
	,	Content( L"Content displayed to user" )
{}

// ================================ //
//
inline void			StringContainer::StringsSet2		()
{
	Description = "User defined Description";
	Content = L"Nothing interesting";
}

}
