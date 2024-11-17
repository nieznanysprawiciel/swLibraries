#include "MockOS.h"



namespace sw {
namespace gui
{


// ================================ //
//
fs::Path			MockOS::GetTempDir			() const
{
	return fs::Path::WorkingDirectory() / "TMP";
}

// ================================ //
//
fs::Path			MockOS::GetApplicationDir	() const
{
	return fs::Path::WorkingDirectory();
}

// ================================ //

fs::Path			MockOS::GetSystemFontsDir() const
{
	// @todo Can we think of better directory?
    return fs::Path::WorkingDirectory();
}


}	// gui
}	// sw


