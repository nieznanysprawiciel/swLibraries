#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/DataBinding/Binding.h"
#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swGUI/Tests/TestBindings/Classes/Animal.h"
#include "swGUI/Tests/TestBindings/Classes/Mammals/Dog.h"

#include "swGUI/TestFramework/Utils/ClassesUI/SubclassTestElement.h"


using namespace sw;


// ================================ //
//
TEST_CASE( "Binding_Create", "[GUI][BindingSystem]" )
{
	gui::DefaultBindingExpressionPtr expression = std::make_shared< gui::DefaultBindingExpression >( "PhysicalProperties.Length" );
	std::unique_ptr< SubclassTestElement > root = std::make_unique< SubclassTestElement >();

	gui::Binding binding( expression, root.get(), TypeID::get< SubclassTestElement >().get_property( "Number" ) );

	CHECK( binding.GetBindingExpression() == expression );
	CHECK( binding.GetBindingMode() == gui::BindingMode::OneWay );
	CHECK( binding.GetUpdateTrigger() == gui::UpdateSourceTrigger::Default );
	CHECK( binding.GetConverter() == nullptr );
	CHECK( binding.GetValidator() == nullptr );
	CHECK_FALSE( binding.GetSourceObject().is_valid() );
	CHECK_FALSE( binding.GetSourceProperty().is_valid() );
	CHECK( binding.GetTargetObject().is_valid() );
	CHECK( binding.GetTargetProperty().is_valid() );

	CHECK( binding.GetTargetObject().get_value< SubclassTestElement* >() == root.get() );
	CHECK( binding.GetTargetProperty() == TypeID::get< SubclassTestElement >().get_property( "Number" ) );
}

// ================================ //
// Evaluates expression internally to find new source property and object.
TEST_CASE( "Binding_UpdateBinding", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< SubclassTestElement > root = std::make_unique< SubclassTestElement >();

	gui::DefaultBindingExpressionPtr expression = std::make_shared< gui::DefaultBindingExpression >( "PhysicalProperties.Length" );
	gui::Binding binding( expression, root.get(), TypeID::get< SubclassTestElement >().get_property( "Number" ) );

	binding.UpdateBinding( root.get(), dog.get() );

	CHECK( binding.GetSourceObject().is_valid() );
	CHECK( binding.GetSourceProperty().is_valid() );

	REQUIRE( binding.GetSourceObject().get_type() == TypeID::get< SubclassTestElement >() );
	CHECK( binding.GetSourceProperty().get_type() == TypeID::get< uint32 >() );

	CHECK( binding.GetSourceObject().get_value< SubclassTestElement* >() == root.get() );
	CHECK( binding.GetSourceProperty() == TypeID::get< SubclassTestElement >().get_property( "Number" ) );
}

