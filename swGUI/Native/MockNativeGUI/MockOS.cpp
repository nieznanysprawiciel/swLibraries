#include "MockOS.h"



namespace sw {
namespace gui
{


// ================================ //
//
filesystem::Path			MockOS::GetTempDir			() const
{
	return filesystem::Path::WorkingDirectory() / "TMP";
}

// ================================ //
//
filesystem::Path			MockOS::GetApplicationDir	() const
{
	return filesystem::Path::WorkingDirectory() / "Application-Dir";
}


}	// gui
}	// sw


