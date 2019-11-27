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



