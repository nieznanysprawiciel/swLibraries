#include "WindowsOS.h"

#include <Windows.h>




namespace sw {
namespace gui
{



// ================================ //
//
fs::Path			WindowsOS::GetTempDir			() const
{
	TCHAR lpTempPathBuffer[ MAX_PATH ];
    auto dwRetVal = GetTempPath( MAX_PATH, lpTempPathBuffer );

	if( dwRetVal > MAX_PATH || ( dwRetVal == 0 ) )
		return "TMP";

	return lpTempPathBuffer;
}

// ================================ //
//
fs::Path			WindowsOS::GetApplicationDir	() const
{
	TCHAR lpTempPathBuffer[ MAX_PATH ];
	int bytes = GetModuleFileName( NULL, lpTempPathBuffer, MAX_PATH );

	if( bytes == 0 )
		return "";

	fs::Path path = lpTempPathBuffer;
	return path.GetParent();	// Get rid of filename.
}

// ================================ //

fs::Path			WindowsOS::GetSystemFontsDir() const
{
	// In the future we shoudl check Registry:
	// HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Fonts

    return fs::Path( "C:\\Windows\\Fonts" );
}


}	// gui
}	// sw

