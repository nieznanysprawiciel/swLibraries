#include "swCommonLib/External/Catch/catch.hpp"


#include "swGUI/Core/System/DataBinding/Expressions/AncestorBindingExpression.h"
#include "swGUI/TestFramework/Utils/ClassesUI/SubclassTestElement.h"

#include "swCommonLib/Common/Properties/Properties.h"


//====================================================================================//
// Tests of AncestorBindingExpression. Evaluation of path is tested in
// TestPathEvaluation tests. These tests check only finding ancestor.
//====================================================================================//


using namespace sw;


// ================================ //
//
std::unique_ptr< gui::UIElement >		CreateControlsTree1	()
{
	std::unique_ptr< SubclassTestElement > root = std::make_unique< SubclassTestElement >();

	TestUIElementClass* level1 = new TestUIElementClass;
	root->AddChild( std::unique_ptr< TestUIElementClass >( level1 ) );

	SubclassTestElement* level2 = new SubclassTestElement;
	level1->AddChild( std::unique_ptr< SubclassTestElement >( level2 ) );

	TestUIElementClass * level3 = new TestUIElementClass;
	level2->AddChild( std::unique_ptr< TestUIElementClass >( level3 ) );

	SubclassTestElement* level4 = new SubclassTestElement;
	level3->AddChild( std::unique_ptr< SubclassTestElement >( level4 ) );

	return std::move( root );
}

// ================================ //
//
gui::UIElement *		GetMostBottomControl	( gui::UIElement * control )
{
	while( control->GetNumChildren() != 0 )
		control = control->GetUIChild( 0 );

	return control;
}

//====================================================================================//
//			Tests	
//====================================================================================//


// ================================ //
//
TEST_CASE( "AncestorBinding_FindFirstLevelAncestor", "[GUI][BindingSystem][Expressions]" )
{
	auto root = CreateControlsTree1();
	auto bindingOwner = GetMostBottomControl( root.get() );
	auto controlToFind = bindingOwner->GetParent()->GetParent();

	gui::AncestorBindingExpressionPtr expression = std::make_shared< gui::AncestorBindingExpression >( "Number", TypeID::get< SubclassTestElement >(), 1 );
	auto bindingTarget = expression->EvaluateExpression( rttr::variant(), bindingOwner );

	REQUIRE( bindingTarget.IsValid() );

	auto tatgetType = bindingTarget.Get().Target.get_type();

	CHECK( Properties::GetRealType( bindingTarget.Get().Target ) == TypeID::get< SubclassTestElement >() );
	CHECK( bindingTarget.Get().Target.get_value< gui::UIElement* >() == controlToFind );

	CHECK( bindingTarget.Get().Property.get_type() == TypeID::get< uint32 >() );
	CHECK( bindingTarget.Get().Property.get_name() == "Number" );
}


