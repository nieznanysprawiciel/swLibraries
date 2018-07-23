#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/DataBinding/Binding.h"
#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Animal.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Dog.h"

#include "swGUI/TestFramework/Utils/ClassesUI/DependencyPropsClass.h"

#include "swCommonLib/Common/Properties/Properties.h"

using namespace sw;


// ================================ //
// Propagation to source should work if binding has the same direction.
TEST_CASE( "Binding_Propagation_ToSource_CompatibilDirection", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );

	auto binding = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Length", gui::BindingMode::OneWayToSource );

	REQUIRE( root->AddBinding( binding ).IsValid() );

	dog->m_physicalProperties.Length = 3;
	root->SetNumberItems( 333 );
	CHECK( dog->m_physicalProperties.Length == 333 );
}

// ================================ //
// Propagation to source should do nothing if binding is set in oposite direction.
TEST_CASE( "Binding_Propagation_ToSource_WrongDirection", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );

	auto binding = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Length", gui::BindingMode::OneWay );

	REQUIRE( root->AddBinding( binding ).IsValid() );

	dog->m_physicalProperties.Length = 3;
	root->SetNumberItems( 333 );
	CHECK( dog->m_physicalProperties.Length == 3 );
}

// ================================ //
// Propagation to target should work if binding has the same direction.
TEST_CASE( "Binding_Propagation_ToTarget_CompatibilDirection", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );

	auto binding = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Length", gui::BindingMode::OneWay );

	REQUIRE( root->AddBinding( binding ).IsValid() );

	// Clear NumberItems value.
	root->SetNumberItems( 333 );

	dog->m_physicalProperties.Length = 541;
	binding->PropagateToTarget();

	CHECK( root->GetNumberItems() == 541 );
}

// ================================ //
// Propagation to target should do nothing if binding is set in oposite direction.
TEST_CASE( "Binding_Propagation_ToTarget_WrongDirection", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );

	auto binding = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Length", gui::BindingMode::OneWayToSource );

	REQUIRE( root->AddBinding( binding ).IsValid() );

	// Clear NumberItems value.
	root->SetNumberItems( 333 );

	dog->m_physicalProperties.Length = 541;
	binding->PropagateToTarget();

	CHECK( root->GetNumberItems() == 333 );
}
