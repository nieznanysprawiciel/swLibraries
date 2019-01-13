/**
@file TestFramework.DX11.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/TestFramework/stdafx.h"
#include "TestFramework.DX11.h"



namespace sw {
namespace gui
{

// ================================ //
//
TestFramework*				GetGlobalTestFramework		()
{
	static TestFramework framework( 0, nullptr );	framework.Init();
	return &framework;
}


}	// gui
}	// sw

