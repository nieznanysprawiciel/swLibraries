#include "WindowsOS.h"

#include <Windows.h>




namespace sw {
namespace gui
{



// ================================ //
//
filesystem::Path			WindowsOS::GetTempDir			() const
{
	TCHAR lpTempPathBuffer[ MAX_PATH ];
    auto dwRetVal = GetTempPath( MAX_PATH, lpTempPathBuffer );

	if( dwRetVal > MAX_PATH || ( dwRetVal == 0 ) )
		return "TMP";

	return lpTempPathBuffer;
}

// ================================ //
//
filesystem::Path			WindowsOS::GetApplicationDir	() const
{
	TCHAR lpTempPathBuffer[ MAX_PATH ];
	int bytes = GetModuleFileName( NULL, lpTempPathBuffer, MAX_PATH );

	if( bytes == 0 )
		return "";

	filesystem::Path path = lpTempPathBuffer;
	return path.GetParent();	// Get rid of filename.
}


}	// gui
}	// sw

