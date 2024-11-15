/**
@file PrototyperUtils.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "PrototyperUtils.h"


namespace sw {
namespace gui
{

// ================================ //
// CoreGUI path should have swGUI in path. We look for this string in binaryPath.
fs::Path		FindCoreGUISourcePath			( const fs::Path& binaryPath )
{
	auto path = binaryPath;
	auto fileName = path.GetFileName();

	while( !fileName.empty() )
	{
		if( fileName == "swGUI" )
		{
			return path;
		}

		path = path.GetParent();
		fileName = path.GetFileName();
	}

	return fs::Path();
}

}	// gui
}	// sw

