#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/RTTR.h"

#include "swGUI/Tests/TestBindings/Classes/Zoo.h"




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

// ================================ //
// Can't set raw pointer property to property of shared_ptr type. This doesn't work in both sides.
TEST_CASE( "RTTR_Behavior_SetMixedWrappedRawPtrProperties", "[RTTR]" )
{
	sw::Zoo	zoo;
	zoo.m_director = new sw::HomoSapiens;
	zoo.m_owner = std::make_shared< sw::HomoSapiens >();

	auto ownerProperty = TypeID::get< sw::Zoo >().get_property( "Owner" );
	auto directorProperty = TypeID::get< sw::Zoo >().get_property( "Director" );

	rttr::variant director = directorProperty.get_value( zoo );
	rttr::variant owner = ownerProperty.get_value( zoo );

	CHECK_FALSE( ownerProperty.set_value( zoo, director ) );
	CHECK_FALSE( directorProperty.set_value( zoo, owner ) );
	CHECK( directorProperty.set_value( zoo, owner.extract_wrapped_value() ) );
}

