/**
@file TestOverrides.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Core/Overrides.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/BaseObject.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/SharedObject.h"


using namespace sw;


//====================================================================================//
//			Helpers	
//====================================================================================//

// ================================ //
//
void            OverrideImpl        ( ISerializer& ser, const rttr::instance& inst, SerialTypeDesc& desc )
{
    ser.EnterObject( "Custom" );
    ser.SetAttribute( "CustomValue", 30 );
    ser.Exit();
}

// ================================ //
//
void            OverrideImpl2       ( ISerializer& ser, const rttr::instance& inst, SerialTypeDesc& desc )
{
    ser.EnterObject( "Custom2" );
    ser.SetAttribute( "CustomValue2", 30 );
    ser.Exit();
}

//====================================================================================//
//			Test cases	
//====================================================================================//


// ================================ //
// Test if we can add serialization override function for single type.
// Properties vector should be filled with properties to serialize.
TEST_CASE( "Serialization.Overrides.Serial.SingleTypeOverride", "[Serialization]" )
{
    Overrides< SerialTypeDesc > overrides;

    overrides.OverrideType( TypeID::get< BaseObject >(), &OverrideImpl );

    auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< BaseObject >() );

    CHECK( *typeDesc.SerializeFun.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
    CHECK( typeDesc.Properties.size() == 1 );
}

// ================================ //
// Check if we can add serialization override function for type and it's all derived types.
TEST_CASE( "Serialization.Overrides.Serial.DerivedTypes", "[Serialization]" )
{
    Overrides< SerialTypeDesc > overrides;

    overrides.OverrideDerived( TypeID::get< BaseObject >(), &OverrideImpl );

    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< BaseObject >() );

        CHECK( *typeDesc.SerializeFun.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 1 );
    }

    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< DerivedObject >() );

        CHECK( *typeDesc.SerializeFun.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 2 );
    }

    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< SharedObject >() );

        CHECK( *typeDesc.SerializeFun.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 2 );
    }

    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< DerivedFromSharedObject >() );

        CHECK( *typeDesc.SerializeFun.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 2 );
    }

    // Check if NotRelated object was not affected.
    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< NotRelated >() );
        CHECK( typeDesc.SerializeFun == nullptr);
    }
}

// ================================ //
// First - override serialization for all derived types from BaseObject.
// Second - override serialization for most derived type DerivedFromSharedObject.
// We expect that all classes derived from BaseObject (including BaseObject) will have first override
// function except DerivedFromSharedObject, which should have second override funcion.
TEST_CASE( "Serialization.Overrides.Serial.DerivedTypes.OverwriteFunction", "[Serialization]" )
{
    Overrides< SerialTypeDesc > overrides;

    overrides.OverrideDerived( TypeID::get< BaseObject >(), &OverrideImpl );
    overrides.OverrideType( TypeID::get< DerivedFromSharedObject >(), &OverrideImpl2 );

    auto& typeDesc1 = overrides.GetTypeDescriptor( TypeID::get< BaseObject >() );
    CHECK( *typeDesc1.SerializeFun.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );

    auto& typeDesc2 = overrides.GetTypeDescriptor( TypeID::get< SharedObject >() );
    CHECK( *typeDesc2.SerializeFun.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );

    auto& typeDesc3 = overrides.GetTypeDescriptor( TypeID::get< DerivedFromSharedObject >() );
    CHECK( *typeDesc3.SerializeFun.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl2 );


    // Check if NotRelated object was not affected.
    auto& typeDesc4 = overrides.GetTypeDescriptor( TypeID::get< NotRelated >() );
    CHECK( typeDesc4.SerializeFun == nullptr );
}


// ================================ //
//
TEST_CASE( "Serialization.Overrides.Deserial.SingleTypeOverride", "[Serialization]" )
{
    Overrides< SerialTypeDesc > overrides;

}
