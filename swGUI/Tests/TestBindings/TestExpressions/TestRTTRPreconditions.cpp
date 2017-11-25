#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/RTTR.h"


//====================================================================================//
// Test rttr library behavior. These test exist to check if something important changes.	
//====================================================================================//


// ================================ //
//
TEST_CASE( "RTTR_Behavior_NullIsValidVariant", "[RTTR]" )
{
	rttr::variant nullVariant( nullptr );
	CHECK( nullVariant.is_valid() );
	CHECK( nullVariant.get_type().is_valid() );
}
