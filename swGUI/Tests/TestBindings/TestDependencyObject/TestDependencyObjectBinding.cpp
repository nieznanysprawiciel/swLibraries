#include "swCommonLib/External/Catch/catch.hpp"

#include "swGUI/Core/System/DataBinding/Binding.h"
#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Animal.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/Animals/Mammals/Dog.h"

#include "swGUI/TestFramework/Utils/ClassesUI/DependencyPropsClass.h"

#include "swCommonLib/Common/Properties/Properties.h"

using namespace sw;



// ================================ //
//
TEST_CASE( "Binding_DependencyObject_BindSingleProperty", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );

	auto binding = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Length", gui::BindingMode::OneWayToSource );

	REQUIRE( root->AddBinding( binding ).IsValid() );

	root->SetNumberItems( 333 );
	CHECK( dog->m_physicalProperties.Length == 333 );

	root->SetNumberItems( 7777 );
	CHECK( dog->m_physicalProperties.Length == 7777 );

	root->SetNumberItems( 33551 );
	CHECK( dog->m_physicalProperties.Length == 33551 );
}

// ================================ //
// 
TEST_CASE( "Binding_DependencyObject_MultipleBindings", "[GUI][BindingSystem]" )
{
	std::unique_ptr< Dog > dog = std::unique_ptr< Dog >( new Dog );
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child1 = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child2 = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( dog.get() );
	child1->SetDataContext( root.get() );
	child2->SetDataContext( root.get() );

	auto binding1 = gui::Binding::Create( "NumberItems", root.get(), "PhysicalProperties.Height", gui::BindingMode::OneWayToSource );
	REQUIRE( root->AddBinding( binding1 ).IsValid() );

	auto binding2 = gui::Binding::Create( "NumberItems", child1.get(), "NumberItems", gui::BindingMode::OneWay );
	REQUIRE( child1->AddBinding( binding2 ).IsValid() );

	auto binding3 = gui::Binding::Create( "NumberItems", child2.get(), "NumberItems", gui::BindingMode::OneWay );
	REQUIRE( child2->AddBinding( binding3 ).IsValid() );

	root->SetNumberItems( 333 );
	CHECK( dog->m_physicalProperties.Height == 333 );
	CHECK( child1->GetNumberItems() == 333 );
	CHECK( child2->GetNumberItems() == 333 );

	root->SetNumberItems( 33551 );
	CHECK( dog->m_physicalProperties.Height == 33551 );
	CHECK( child1->GetNumberItems() == 33551 );
	CHECK( child2->GetNumberItems() == 33551 );
}

// ================================ //
// Bind to property, that has no binding. I this case system must create link between these to properties.
TEST_CASE( "Binding_DependencyObject_BindToPropertyWithoutBinding", "[GUI][BindingSystem]" )
{
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( child.get() );

	// ContainerName property of "child" object has no bindings. We set propagation direction to root.
	auto binding = gui::Binding::Create( "ContainerName", root.get(), "ContainerName", gui::BindingMode::OneWay );
	REQUIRE( root->AddBinding( binding ).IsValid() );

	child->SetContainerName( "Newly set value" );
	CHECK( root->GetContainerName() == "Newly set value" );
}

// ================================ //
// Circular dependancies shouldn't cause dead lock.
TEST_CASE( "Binding_DependencyObject_CircularDependencies", "[GUI][BindingSystem]" )
{
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child1 = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child2 = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child3 = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child4 = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( child1.get() );
	child1->SetDataContext( child2.get() );
	child2->SetDataContext( child3.get() );
	child3->SetDataContext( child4.get() );
	child4->SetDataContext( root.get() );

	REQUIRE( root->AddBinding( gui::Binding::Create( "NumberItems", root.get(), "NumberItems", gui::BindingMode::OneWay ) ).IsValid() );
	REQUIRE( child1->AddBinding( gui::Binding::Create( "NumberItems", child1.get(), "NumberItems", gui::BindingMode::OneWay ) ).IsValid() );
	REQUIRE( child2->AddBinding( gui::Binding::Create( "NumberItems", child2.get(), "NumberItems", gui::BindingMode::OneWay ) ).IsValid() );
	REQUIRE( child3->AddBinding( gui::Binding::Create( "NumberItems", child3.get(), "NumberItems", gui::BindingMode::OneWay ) ).IsValid() );
	REQUIRE( child4->AddBinding( gui::Binding::Create( "NumberItems", child4.get(), "NumberItems", gui::BindingMode::OneWay ) ).IsValid() );

	CHECK_NOTHROW( root->SetNumberItems( 675 ) );

	CHECK( root->GetNumberItems() == 675 );
	CHECK( child1->GetNumberItems() == 675 );
	CHECK( child2->GetNumberItems() == 675 );
	CHECK( child3->GetNumberItems() == 675 );
	CHECK( child4->GetNumberItems() == 675 );
}

// ================================ //
// Test TwoWay binding mode. Setting value shouldn't cause dead locks.
TEST_CASE( "Binding_DependencyObject_TwoWayBinding", "[GUI][BindingSystem]" )
{
	std::unique_ptr< gui::DependencyPropsClass > root = std::make_unique< gui::DependencyPropsClass >();
	std::unique_ptr< gui::DependencyPropsClass > child = std::make_unique< gui::DependencyPropsClass >();

	root->SetDataContext( child.get() );

	auto binding = gui::Binding::Create( "ContainerName", root.get(), "ContainerName", gui::BindingMode::TwoWay );
	REQUIRE( root->AddBinding( binding ).IsValid() );

	// To target direction.
	CHECK_NOTHROW( child->SetContainerName( "Newly set value" ) );
	CHECK( root->GetContainerName() == "Newly set value" );
	CHECK( child->GetContainerName() == "Newly set value" );

	// To source direction.
	CHECK_NOTHROW( root->SetContainerName( "Value number 2" ) );
	CHECK( root->GetContainerName() == "Value number 2" );
	CHECK( child->GetContainerName() == "Value number 2" );
}


