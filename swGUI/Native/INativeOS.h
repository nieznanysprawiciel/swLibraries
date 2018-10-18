#pragma once
/**
@file INativeOS.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/System/Path.h"


namespace sw {
namespace gui
{



/**@brief Interface for system dependent calls.*/
class INativeOS
{
private:
protected:
public:
	explicit		INativeOS		() = default;
	virtual			~INativeOS		() = default;

public:

	virtual	filesystem::Path		GetTempDir		() const = 0;

};




}	// gui
}	// sw


