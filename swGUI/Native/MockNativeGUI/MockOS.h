#pragma once
/**
@file MockOS.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Native/INativeOS.h"


namespace sw {
namespace gui
{


/**@brief Emulates operating system calls.*/
class MockOS : public INativeOS
{
private:
protected:
public:
	explicit		MockOS		() = default;
	virtual			~MockOS		() = default;


public:

	virtual fs::Path			GetTempDir			() const override;
	virtual fs::Path			GetApplicationDir	() const override;
    virtual fs::Path            GetSystemFontsDir	() const override;
};



}	// gui
}	// sw

