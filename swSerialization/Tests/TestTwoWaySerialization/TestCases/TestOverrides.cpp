/**
@file TestOverrides.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"

#include "swSerialization/Serialization/Core/Overrides.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/BaseObject.h"


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

//====================================================================================//
//			Test cases	
//====================================================================================//


// ================================ //
//
TEST_CASE( "Serialization.Overrides.Serial.SingleTypeOverride", "[Serialization]" )
{
    Overrides< SerialTypeDesc > overrides;

    overrides.OverrideType( TypeID::get< BaseObject >(), &OverrideImpl );

    auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< BaseObject >() ).SerializeFun;
    CHECK( *typeDesc.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
}


// ================================ //
//
TEST_CASE( "Serialization.Overrides.Deserial.SingleTypeOverride", "[Serialization]" )
{
    Overrides< SerialTypeDesc > overrides;

}

