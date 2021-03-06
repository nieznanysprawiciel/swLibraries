#include "swGraphicAPI/Tests/TestResourceManager/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
/**
@file TestPathsManager.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/ResourceManager/PathTranslators/PathsManager.h"




// ================================ //
// Register new alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.ValidAlias", "[GUISystem][PathsManager]" )
{
	sw::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	
	REQUIRE( result.IsValid() == true );
	CHECK( pathsManager.FindAlias( "$(BLABLA_DIR)" ).IsValid() == true );
}

// ================================ //
// Don't register invalid alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.InvalidAlias", "[GUISystem][PathsManager]" )
{
	sw::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "BLABLA_DIR", "C:\\blabla/blabla" );
	
	REQUIRE( result.IsValid() == false );
	CHECK( pathsManager.FindAlias( "$(BLABLA_DIR)" ).IsValid() == false );
}

// ================================ //
// Don't register existing alias.
TEST_CASE( "GUI.PathsManager.AliasRegister.Existing", "[GUISystem][PathsManager]" )
{
	sw::PathsManager pathsManager;

	pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	
	REQUIRE( result.IsValid() == false );
	CHECK( pathsManager.FindAlias( "$(BLABLA_DIR)" ).IsValid() == true );
}


// ================================ //
// Translate path using alias.
TEST_CASE( "GUI.PathsManager.Translate.ExistingAlias", "[GUISystem][PathsManager]" )
{
	sw::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == true );

	auto path = pathsManager.Translate( "$(BLABLA_DIR)/gooddir/goodfile.txt" );
	CHECK( path == "C:\\blabla/blabla/gooddir/goodfile.txt" );
}


// ================================ //
// Translate path using not existing alias. Path remains unchanged.
TEST_CASE( "GUI.PathsManager.Translate.NotExistingAlias", "[GUISystem][PathsManager]" )
{
	sw::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "C:\\blabla/blabla" );
	REQUIRE( result.IsValid() == true );

	auto path = pathsManager.Translate( "$(WORKING_DIR)/gooddir/goodfile.txt" );
	CHECK( path == "$(WORKING_DIR)/gooddir/goodfile.txt" );
}

// ================================ //
// Create alias with path, that references other xisting alias.
// Path should be resolved correctly.
TEST_CASE( "GUI.PathsManager.Translate.AliasReferenceInAlias", "[GUISystem][PathsManager]" )
{
	sw::PathsManager pathsManager;

	sw::ReturnResult result = pathsManager.RegisterAlias( "$(TMP_DIR)", "C:\\blabla/tmp" );
	REQUIRE( result.IsValid() == true );

	result = pathsManager.RegisterAlias( "$(BLABLA_DIR)", "$(TMP_DIR)/blabla/not_tmp" );
	REQUIRE( result.IsValid() == true );

	auto path = pathsManager.Translate( "$(BLABLA_DIR)/gooddir/goodfile.txt" );
	CHECK( path == "C:\\blabla/tmp//blabla/not_tmp/gooddir/goodfile.txt" );
}

