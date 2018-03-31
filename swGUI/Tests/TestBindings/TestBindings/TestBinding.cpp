#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/DataBinding/Binding.h"
#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Animal.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Dog.h"

#include "swGUI/TestFramework/Utils/ClassesUI/SubclassTestElement.h"

#include "swCommonLib/Common/Properties/Properties.h"

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
	CHECK( binding.GetTargetProperty().is_valid() );
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

	REQUIRE( binding.UpdateBinding( dog.get() ).IsValid() );

	CHECK( binding.GetSourceObject().is_valid() );
	CHECK( binding.GetSourceProperty().is_valid() );

	REQUIRE( Properties::GetRealType( binding.GetSourceObject() ) == TypeID::get< PhysicalProperties >() );
	CHECK( binding.GetSourceProperty().get_type() == TypeID::get< uint32 >() );

	CHECK( binding.GetSourceObject().get_value< PhysicalProperties* >() == &dog->m_physicalProperties );
	CHECK( binding.GetSourceProperty().get_name() == "Length" );
}

// ================================ //
// Propagetes value to bound property.
TEST_CASE( "Binding_PropagateToSource", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< SubclassTestElement > root = std::make_unique< SubclassTestElement >();

	gui::DefaultBindingExpressionPtr expression = std::make_shared< gui::DefaultBindingExpression >( "PhysicalProperties.Length" );
	gui::Binding binding( expression, root.get(), TypeID::get< SubclassTestElement >().get_property( "Number" ) );
	binding.SetBindingMode( gui::BindingMode::OneWayToSource );

	REQUIRE( binding.UpdateBinding( dog.get() ).IsValid() );

	root->SetNumber( 543 );
	binding.PropagateToSource();

	CHECK( dog->m_physicalProperties.Length == 543 );

	root->SetNumber( 554222 );
	binding.PropagateToSource();

	CHECK( dog->m_physicalProperties.Length == 554222 );
}
