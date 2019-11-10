/**
@file TestSerialType.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

#include "swSerialization/Interfaces/SerialGeneric.h"


using namespace sw;



// ================================ //
//
TEST_CASE( "Serializer.API.SerialType.IsArray", "[Serializers]" )
{
    CHECK( SerialGeneric::IsArray( SerialType::Array ) == true );
    CHECK( SerialGeneric::IsArray( SerialType::Object ) == true );
    CHECK( SerialGeneric::IsArray( SerialType::Attribute ) == false );
    CHECK( SerialGeneric::IsArray( SerialType::Bool ) == false );
    CHECK( SerialGeneric::IsArray( SerialType::Character ) == false );
    CHECK( SerialGeneric::IsArray( SerialType::Double ) == false );
    CHECK( SerialGeneric::IsArray( SerialType::Int64 ) == false );
    CHECK( SerialGeneric::IsArray( SerialType::UInt64 ) == false );
    CHECK( SerialGeneric::IsArray( SerialType::String ) == false );
    CHECK( SerialGeneric::IsArray( SerialType::Number ) == false );
}

// ================================ //
//
TEST_CASE( "Serializer.API.SerialType.IsObject", "[Serializers]" )
{
    CHECK( SerialGeneric::IsObject( SerialType::Array ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::Object ) == true );
    CHECK( SerialGeneric::IsObject( SerialType::Attribute ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::Bool ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::Character ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::Double ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::Int64 ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::UInt64 ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::String ) == false );
    CHECK( SerialGeneric::IsObject( SerialType::Number ) == false );
}

