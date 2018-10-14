#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/Config/PathsManager.h"




// ================================ //
// Register new alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.ValidAlias", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( L"$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == true );
}

// ================================ //
// Don't register invalid alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.InvalidAlias", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( L"BLABLA_DIR", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == false );
}

// ================================ //
// Don't register existing alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.Existing", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	pathsManager.RegisterAlias( L"$(BLABLA_DIR)", "C:\\blabla/blabla" );
	sw::ReturnResult result = pathsManager.RegisterAlias( L"$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == false );
}
