/**
@file ExtendedMacros.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



// ================================ //
// Checks nullable IsValid and prints exception
// if there's an error.
#define REQUIRE_IS_VALID( nullable )			\
if( !nullable.IsValid() )						\
{												\
	INFO( nullable.GetErrorReason() );			\
	REQUIRE( nullable.IsValid() == true );		\
}


