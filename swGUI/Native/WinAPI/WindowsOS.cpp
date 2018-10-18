#include "WindowsOS.h"

#include <Windows.h>




namespace sw {
namespace gui
{



// ================================ //
//
filesystem::Path			WindowsOS::GetTempDir		() const
{
	TCHAR lpTempPathBuffer[ MAX_PATH ];
    auto dwRetVal = GetTempPath( MAX_PATH, lpTempPathBuffer );

	if( dwRetVal > MAX_PATH || ( dwRetVal == 0 ) )
		return "TMP";

	return lpTempPathBuffer;
}


}	// gui
}	// sw

