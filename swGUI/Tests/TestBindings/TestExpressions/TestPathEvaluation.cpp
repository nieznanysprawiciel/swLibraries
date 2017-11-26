#include "swCommonLib/External/Catch/catch.hpp"


#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swGUI/Tests/TestBindings/Classes/Animal.h"
#include "swGUI/Tests/TestBindings/Classes/Mammals/Dog.h"

#include <memory>


using namespace sw;


// ================================ //
// Evalute binding target by using DefaultBindingExpression. Pass path containing only single property name.
// Set simple base class as DataContext. propertyOwner parameter should be ignored.
TEST_CASE( "PathEvaluation_OneElementPath", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Animal > animal = std::unique_ptr< Animal >( new Animal );
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( animal.get(), "Name" );

	REQUIRE( bindingTarget.IsValid() );
	
	CHECK( bindingTarget.Get().Property.get_name() == "Name" );

	// Property types is reference wrapper to string, so we must check wrapped type.
	CHECK( bindingTarget.Get().Property.get_type().get_wrapped_type() == TypeID::get< std::string >() );
	CHECK( bindingTarget.Get().Property.get_declaring_type() == TypeID::get< sw::Animal >() );

	CHECK( bindingTarget.Get().Target.get_value< Animal* >() == animal.get() );
}


// ================================ //
// Evalute binding target by using DefaultBindingExpression. Pass path to non existing property.
// EvaluateExpression should return invalid BindingTarget nullable.
TEST_CASE( "PathEvaluation_PassNonExistingPropertyPath", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Animal > animal = std::unique_ptr< Animal >( new Animal );
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( animal.get(), "NonExistingProperty" );

	REQUIRE_FALSE( bindingTarget.IsValid() );
}

// ================================ //
//
TEST_CASE( "PathEvaluation_PassNullDataContext", "[GUI][BindingSystem][Expressions]" )
{
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( rttr::variant( nullptr ), "NonExistingProperty" );

	REQUIRE_FALSE( bindingTarget.IsValid() );
}

// ================================ //
// Empty binding path should resolve to invalid property and valid object equal to data context.
TEST_CASE( "PathEvaluation_EmptyBindingPath", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Animal > animal = std::unique_ptr< Animal >( new Animal );
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( animal.get(), "" );

	REQUIRE( bindingTarget.IsValid() );

	auto & property = bindingTarget.Get().Property;
	auto & target = bindingTarget.Get().Target;

	CHECK_FALSE( property.is_valid() );
	CHECK( target.is_valid() );

	CHECK( target.get_type() == TypeID::get< Animal* >() );
	CHECK( target.get_value< Animal* >() == animal.get() );
}

// ================================ //
// Evaluate path to property in subclass using variant created from base class.
TEST_CASE( "PathEvaluation_PathToPropertyInSubclass", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	Animal* animal = dog.get();

	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( animal, "Race" );
	REQUIRE( bindingTarget.IsValid() );

	auto & property = bindingTarget.Get().Property;
	auto & target = bindingTarget.Get().Target;

	CHECK( property.is_valid() );
	CHECK( target.is_valid() );

	CHECK( bindingTarget.Get().Property.get_type().get_wrapped_type() == TypeID::get< std::string >() );
	CHECK( bindingTarget.Get().Property.get_declaring_type() == TypeID::get< sw::Dog >() );

	CHECK( target.get_value< Animal* >() == dog.get() );
}

// ================================ //
// Property path contains at beginning valid path, but last valid element is basic c++ type and
// path tries to access property in it.
TEST_CASE( "PathEvaluation_TryAccessPropertyOfSimpleType", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Animal > animal = std::unique_ptr< Animal >( new Animal );
	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( animal.get(), "Age.Name" );

	REQUIRE_FALSE( bindingTarget.IsValid() );
}

// ================================ //
// Path with 2 properties levels. Target should point to one before last object on path.
TEST_CASE( "PathEvaluation_TwoLevelsPath", "[GUI][BindingSystem][Expressions]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );

	auto bindingTarget = gui::DefaultBindingExpression::EvaluateRelativeProperty( dog.get(), "PhysicalProperties.Weight" );
	REQUIRE( bindingTarget.IsValid() );

	auto & property = bindingTarget.Get().Property;
	auto & target = bindingTarget.Get().Target;

	CHECK( property.is_valid() );
	CHECK( target.is_valid() );

	CHECK( bindingTarget.Get().Property.get_type() == TypeID::get< float >() );
	CHECK( bindingTarget.Get().Property.get_declaring_type() == TypeID::get< sw::PhysicalProperties >() );

	CHECK( target.get_type().get_raw_type() == TypeID::get< sw::PhysicalProperties >() );
	CHECK( target.get_value< sw::PhysicalProperties* >() == &dog->m_physicalProperties );
}

