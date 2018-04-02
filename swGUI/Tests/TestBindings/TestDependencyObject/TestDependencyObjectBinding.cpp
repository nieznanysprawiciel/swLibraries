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

	gui::DefaultBindingExpressionPtr expression = std::make_shared< gui::DefaultBindingExpression >( "PhysicalProperties.Length" );
	auto binding = std::make_shared< gui::Binding >( expression, root.get(), TypeID::get< gui::DependencyPropsClass >().get_property( "NumberItems" ) );

	REQUIRE( root->AddBinding( binding ).IsValid() );

	root->SetNumberItems( 333 );
	CHECK( dog->m_physicalProperties.Length == 333 );

	root->SetNumberItems( 7777 );
	CHECK( dog->m_physicalProperties.Length == 7777 );

	root->SetNumberItems( 33551 );
	CHECK( dog->m_physicalProperties.Length == 33551 );
}

