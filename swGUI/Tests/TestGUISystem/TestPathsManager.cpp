#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/Config/PathsManager.h"




// ================================ //
// Register new alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.ValidAlias", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == true );
}

// ================================ //
// Don't register invalid alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.InvalidAlias", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "BLABLA_DIR", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == false );
}

// ================================ //
// Don't register existing alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.Existing", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == false );
}


// ================================ //
// Translate path using alias.
TEST_CASE( "GUI.PathsManager.Translate.ExistingAlias", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == true );

	auto path = pathsManager.Translate( "$(BLABLA_DIR)/gooddir/goodfile.txt" );
	CHECK( path == "C:\\blabla/blabla/gooddir/goodfile.txt" );
}


// ================================ //
// Translate path using not existing alias. Path remains unchanged.
TEST_CASE( "GUI.PathsManager.Translate.NotExistingAlias", "[GUISystem][PathsManager]" )
{
	sw::gui::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == true );

	auto path = pathsManager.Translate( "$(WORKING_DIR)/gooddir/goodfile.txt" );
	CHECK( path == "$(WORKING_DIR)/gooddir/goodfile.txt" );
}

