/**
@file TestSerializerInternals.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"


#include "swSerialization/Serializers/SerializerJson/SerializerJSON.h"
#include "swSerialization/Serializers/SerializerJson/NodesRegistry.h"


using namespace sw;



// ================================ //
//
TEST_CASE( "Serializer.JSON.Internals.ToNodePtr", "[Serializers][SerializerXML]" )
{
    impl::NodePointerImpl ptrImpl( 1, 2 );
    auto nodePtr = impl::NodesRegistry::ToNodePtr( ptrImpl );

    auto ptrImplRetrieved = impl::NodesRegistry::FromNodePtr( nodePtr );

    CHECK( ptrImplRetrieved.NodeIdx == 1 );
    CHECK( ptrImplRetrieved.ParentIdx == 2 );
}

// ================================ //
// SerialObjects can't store persistent pointers, because json serializer arrays
// can reallocate memory for nodes. This test checks if NodeRegistry correctly updates
// pointers in internal structures.
TEST_CASE( "Serializer.JSON.Internals.NodeRegistry.UpdateNodes", "[Serializers][SerializerJSON]" )
{
    {
        SerializerJSON ser( std::make_unique< ISerializationContext >() );
        SerialObject root = ser.Root();

        auto firstObject = root.AddObject( "FirstObject" );

        // Default object capcity is 16. Add attributes to cause reallocation.
        // But it's a little bit more complicated to cause something bad happen.
        // Json nodes aren't deallocated, so they contain old pointers to children nodes.
        // We must fill firstObject to it's limit, than fill root and cause deallocation,
        // and than try to add additional node to firstObject.
        for( int i = 0; i < 16; ++i )
            firstObject.AddAttribute( fmt::format( "Value-{}", i ), i );

        // Here deallocation will happen.
        for( int i = 0; i < 17; ++i )
            root.AddAttribute( fmt::format( "Value-{}", i ), i );

        firstObject.AddAttribute( "Value", "Expected value" );

        auto saveResult = ser.SaveFile( "SerializerTest/JSON/Generated/Test-NodeRegistry-UpdateNodes.json", sw::WritingMode::Readable );
        REQUIRE_IS_VALID( saveResult );
    }

    {
        SerializerJSON deser( std::make_unique< ISerializationContext >() );
        auto loadResult = deser.LoadFromFile( "SerializerTest/JSON/Generated/Test-NodeRegistry-UpdateNodes.json" );
        REQUIRE_IS_VALID( loadResult );

        SerialObject root = deser.Root();
        REQUIRE( root.GetElement( "FirstObject" ).has_value() );
        REQUIRE( root.GetElement( "FirstObject" ).value().IsObject() );

        SerialObject firstObject = root.GetElement( "FirstObject" ).value().ObjectView().value();
        auto valueAttribute = firstObject.GetElement( "Value" ).value().AttributeView().value();

        REQUIRE( valueAttribute.ConvertToString().has_value() == true );
        CHECK( valueAttribute.ConvertToString().value() == "Expected value" );
    }
}


