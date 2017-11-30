#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/DataBinding/Binding.h"
#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swGUI/Tests/TestBindings/Classes/Animal.h"
#include "swGUI/Tests/TestBindings/Classes/Mammals/Dog.h"



using namespace sw;


// ================================ //
//
TEST_CASE( "Binding_Create", "[GUI][BindingSystem]" )
{
	gui::DefaultBindingExpressionPtr expression = std::make_shared< gui::DefaultBindingExpression >( "PhysicalProperties.Length" );
	gui::Binding binding( expression );

	CHECK( binding.GetBindingExpression() == expression );
	CHECK( binding.GetBindingMode() == gui::BindingMode::OneWay );
	CHECK( binding.GetUpdateTrigger() == gui::UpdateSourceTrigger::Default );
	CHECK( binding.GetConverter() == nullptr );
	CHECK( binding.GetValidator() == nullptr );
	CHECK_FALSE( binding.GetSourceObject().is_valid() );
	CHECK_FALSE( binding.GetSourceProperty().is_valid() );
	CHECK_FALSE( binding.GetTargetObject().is_valid() );
	CHECK_FALSE( binding.GetTargetProperty().is_valid() );


}

