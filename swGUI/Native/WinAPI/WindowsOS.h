#pragma once
/**
@file WindowsOS.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Native/INativeOS.h"


namespace sw {
namespace gui
{

/**@brief Windows calls.*/
class WindowsOS : public INativeOS
{
private:
protected:
public:
	explicit		WindowsOS		() = default;
	virtual			~WindowsOS		() = default;


public:

	virtual fs::Path			GetTempDir			() const override;
	virtual fs::Path			GetApplicationDir	() const override;

};


}	// gui
}	// sw

