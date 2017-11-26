#include "swCommonLib/External/Catch/catch.hpp"


#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swGUI/Tests/TestBindings/Classes/Animal.h"
#include "swGUI/Tests/TestBindings/Classes/Mammals/Dog.h"


//====================================================================================//
// Tests of DefaultBindingExpression. Most of functionality of this class it evaluation
// of path in function EvaluateRelativeProperty. This funtion has separate tests.
//====================================================================================//


using namespace sw;


// ================================ //
// Path with 2 properties levels. Target should point to one before last object on path.
TEST_CASE( "DefaultBindingExpression_SimpleEvaluation", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	gui::DefaultBindingExpressionPtr expression = std::make_shared< gui::DefaultBindingExpression >( "PhysicalProperties.Length" );

	auto bindingTarget = expression->EvaluateExpression( dog.get(), rttr::variant() );
	REQUIRE( bindingTarget.IsValid() );

	auto & property = bindingTarget.Get().Property;
	auto & target = bindingTarget.Get().Target;

	CHECK( property.is_valid() );
	CHECK( target.is_valid() );

	CHECK( bindingTarget.Get().Property.get_type() == TypeID::get< uint32 >() );
	CHECK( bindingTarget.Get().Property.get_declaring_type() == TypeID::get< sw::PhysicalProperties >() );

	CHECK( target.get_type().get_raw_type() == TypeID::get< sw::PhysicalProperties >() );
	CHECK( target.get_value< sw::PhysicalProperties* >() == &dog->m_physicalProperties );
}

