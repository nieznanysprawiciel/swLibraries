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


}	// gui
}	// sw


