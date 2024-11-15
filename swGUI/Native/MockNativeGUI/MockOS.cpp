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


}	// gui
}	// sw


