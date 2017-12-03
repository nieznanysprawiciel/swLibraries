#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/DataBinding/Binding.h"
#include "swCommonLib/Common/Properties/Properties.h"

#include "swGUI/Tests/TestBindings/Classes/Animal.h"
#include "swGUI/Tests/TestBindings/Classes/Mammals/Dog.h"

#include "swGUI/TestFramework/Utils/ClassesUI/SubclassTestElement.h"


#include "swGUI/TestFramework/Testers/Bindings/TesterBinding.h"


using namespace sw;







// ================================ //
//
TEST_CASE_METHOD( gui::CLASS_TESTER( Binding ), "Binding_Compatibility", "[GUI][BindingSystem]" )
{
	gui::Binding binding( nullptr, nullptr, Properties::EmptyProperty() );

	SECTION( "EqualTypes_OneWayMode" )
	{
		binding.SetBindingMode( gui::BindingMode::OneWay );
		CHECK( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< Dog* >() ).IsValid() );
	}

	SECTION( "EqualTypes_OneTimeMode" )
	{
		binding.SetBindingMode( gui::BindingMode::OneTime );
		CHECK( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< Dog* >() ).IsValid() );
	}

	SECTION( "EqualTypes_OneWayToSourceMode" )
	{
		binding.SetBindingMode( gui::BindingMode::OneWayToSource );
		CHECK( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< Dog* >() ).IsValid() );
	}

	SECTION( "EqualTypes_TwoWayMode" )
	{
		binding.SetBindingMode( gui::BindingMode::TwoWay );
		CHECK( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< Dog* >() ).IsValid() );
	}

	SECTION( "EqualTypes_BasicTypes" )
	{
		binding.SetBindingMode( gui::BindingMode::OneWay );
		CHECK( ValidateBinding( binding, TypeID::get< uint32 >(), TypeID::get< uint32 >() ).IsValid() );
	}

	SECTION( "DifferentTypes_IntTypes" )
	{
		binding.SetBindingMode( gui::BindingMode::OneWay );
		CHECK( ValidateBinding( binding, TypeID::get< uint32 >(), TypeID::get< int64 >() ).IsValid() );
	}

	SECTION( "DifferentTypes_FloatTypes" )
	{
		binding.SetBindingMode( gui::BindingMode::TwoWay );
		CHECK( ValidateBinding( binding, TypeID::get< uint32 >(), TypeID::get< float >() ).IsValid() );
	}

	SECTION( "DerivedTypes_ToTargetMode" )
	{
		binding.SetBindingMode( gui::BindingMode::OneWay );
		CHECK( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< Mammal* >() ).IsValid() );
	}

	SECTION( "DerivedTypes_ToSourceMode" )
	{
		binding.SetBindingMode( gui::BindingMode::OneWayToSource );
		CHECK( ValidateBinding( binding, TypeID::get< Mammal* >(), TypeID::get< Dog* >() ).IsValid() );
	}

	SECTION( "DerivedTypes_DifferentTypes_TwoWayMode" )
	{
		binding.SetBindingMode( gui::BindingMode::TwoWay );
		CHECK_FALSE( ValidateBinding( binding, TypeID::get< Mammal* >(), TypeID::get< Dog* >() ).IsValid() );
	}

	SECTION( "DerivedTypes_EqualTypes_TwoWayMode" )
	{
		binding.SetBindingMode( gui::BindingMode::TwoWay );
		CHECK( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< Dog* >() ).IsValid() );
	}

	SECTION( "UnrelatedTypes_TwoWayMode" )
	{
		binding.SetBindingMode( gui::BindingMode::TwoWay );
		CHECK_FALSE( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< uint32 >() ).IsValid() );
	}

	SECTION( "UnrelatedTypes_OneWayMode" )
	{
		binding.SetBindingMode( gui::BindingMode::OneWay );
		CHECK_FALSE( ValidateBinding( binding, TypeID::get< Dog* >(), TypeID::get< uint32 >() ).IsValid() );
	}
}
