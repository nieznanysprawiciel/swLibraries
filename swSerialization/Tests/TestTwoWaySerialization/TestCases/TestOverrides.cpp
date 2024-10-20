/**
@file TestOverrides.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/Tests/TestTwoWaySerialization/PrecompiledHeader/stdafx.h"
#include "swCommonLib/External/Catch/catch.hpp"
#include "swCommonLib/TestUtils/CatchUtils/ExtendedMacros.h"

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

// ================================ //
//
Nullable< VariantWrapper >        DeserOverrideImpl      ( const IDeserializer& deser, 
                                                           TypeID expectedType, 
                                                           rttr::variant& prevValue, 
                                                           DeserialTypeDesc& desc )
{
    return "Fail";
}

//====================================================================================//
//			Unit tests of Overrides<> template
//====================================================================================//


// ================================ //
// Test if we can add serialization override function for single type.
// Properties vector should be filled with properties to serialize.
TEST_CASE( "Serialization.Overrides.Serial.SingleTypeOverride", "[Serialization]" )
{
    Overrides< SerialTypeDesc > overrides;

    overrides.OverrideType( TypeID::get< BaseObject >(), &OverrideImpl );

    auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< BaseObject >() );

    CHECK( *typeDesc.CustomFunction.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
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

        CHECK( *typeDesc.CustomFunction.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 1 );
    }

    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< DerivedObject >() );

        CHECK( *typeDesc.CustomFunction.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 2 );
    }

    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< SharedObject >() );

        CHECK( *typeDesc.CustomFunction.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 2 );
    }

    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< DerivedFromSharedObject >() );

        CHECK( *typeDesc.CustomFunction.target< void( * )( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );
        CHECK( typeDesc.Properties.size() == 2 );
    }

    // Check if NotRelated object was not affected.
    {
        auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< NotRelated >() );
        CHECK( typeDesc.CustomFunction == nullptr);
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
    CHECK( *typeDesc1.CustomFunction.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );

    auto& typeDesc2 = overrides.GetTypeDescriptor( TypeID::get< SharedObject >() );
    CHECK( *typeDesc2.CustomFunction.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl );

    auto& typeDesc3 = overrides.GetTypeDescriptor( TypeID::get< DerivedFromSharedObject >() );
    CHECK( *typeDesc3.CustomFunction.target< void(*)( ISerializer&, const rttr::instance&, SerialTypeDesc& )>() == OverrideImpl2 );


    // Check if NotRelated object was not affected.
    auto& typeDesc4 = overrides.GetTypeDescriptor( TypeID::get< NotRelated >() );
    CHECK( typeDesc4.CustomFunction == nullptr );
}


// ================================ //
// Check if instantiation for deserializer works. Logic is tested in serializer instatiation.
TEST_CASE( "Serialization.Overrides.Deserial.SingleTypeOverride", "[Serialization]" )
{
    Overrides< DeserialTypeDesc > overrides;

    overrides.OverrideType( TypeID::get< BaseObject >(), &DeserOverrideImpl );

    auto& typeDesc = overrides.GetTypeDescriptor( TypeID::get< BaseObject >() );

    CHECK( *typeDesc.CustomFunction.target< Nullable< VariantWrapper >(*)( const IDeserializer&, TypeID, rttr::variant&, DeserialTypeDesc& ) >() == DeserOverrideImpl );
    CHECK( typeDesc.Properties.size() == 1 );
}

//====================================================================================//
//			Overrides<> integration tests with full serialization (helpers)
//====================================================================================//

// ================================ //
//
ReturnResult                      SetDataset                        ( StructWithSimpleTypes& structToSet, uint32 dataset )
{
    switch( dataset )
    {
    case 1:
        structToSet.FillWithDataset1();
        break;
    case 2:
        structToSet.FillWithDataset2();
        break;
    case 3:
        structToSet.FillWithDataset3();
        break;
    case 4:
        structToSet.FillWithDataset4();
        break;
    default:
        return "No dataset";
    }
    return Success::True;
}

// ================================ //
//
void            OverrideHardcodeDataset                             ( ISerializer& ser,
                                                                      const rttr::instance& inst,
                                                                      SerialTypeDesc& desc )
{
    ser.SetAttribute( "Dataset", 3 );
}

// ================================ //
//
Nullable< VariantWrapper >        DeserOverrideHardcodeDataset      ( const IDeserializer& deser,
                                                                      TypeID expectedType,
                                                                      rttr::variant& prevValue,
                                                                      DeserialTypeDesc& desc )
{
    BaseObject* newObject = new BaseObject;
    auto& obj = newObject->m_simpleStruct1;

    auto dataset = deser.GetAttribute( "Dataset", 0 );
    auto result = SetDataset( obj, dataset );
    return result.Ok( VariantWrapper::FromNew( newObject ) );
}

// ================================ //
//
Nullable< VariantWrapper >        DeserInPlaceHardcodeDataset      ( const IDeserializer& deser,
                                                                     TypeID expectedType,
                                                                     rttr::variant& prevValue,
                                                                     DeserialTypeDesc& desc)
{
    if (prevValue.can_convert< std::reference_wrapper<BaseObject> >() == false)
        return fmt::format("Can't convert instance to 'Bstd::reference_wrapper<BaseObject>'. Type: {}",
            prevValue.get_type().get_name().to_string());

    auto obj = prevValue.get_value< std::reference_wrapper<BaseObject>>();

    auto dataset = deser.GetAttribute("Dataset", 0);
    auto result = SetDataset(obj.get().m_simpleStruct1, dataset);
    return result.Ok(VariantWrapper::FromPrevious(prevValue));
}


// ================================ //
//
Nullable< VariantWrapper >        DeserOverrideHardcodeDatasetStruct( const IDeserializer& deser,
                                                                      TypeID expectedType,
                                                                      rttr::variant& prevValue,
                                                                      DeserialTypeDesc& desc )
{
    if (prevValue.can_convert< std::reference_wrapper< StructWithSimpleTypes > >() == false)
        return fmt::format("Can't convert instance to 'std::reference_wrapper< StructWithSimpleTypes > >'");

    auto& obj = prevValue.get_value< std::reference_wrapper< StructWithSimpleTypes > >();
    auto dataset = deser.GetAttribute( "Dataset", 0 );

    auto result = SetDataset( obj, dataset );
    return result.Ok( VariantWrapper::FromPrevious( prevValue ) );
}


//====================================================================================//
//			Overrides<> integration tests with full serialization (test cases)
//====================================================================================//

// ================================ //
// Serialize dataset number instead of whole structure.
// Test checks, if override will be used or default serialization function.
// Here we use polymorphic type serialized as top level object.
TEST_CASE( "Serialization.Overrides.Polymorphic.TopLevel", "[Serialization]" )
{
    BaseObject expected;
    BaseObject actual;
    expected.m_simpleStruct1.FillWithDataset3();
    actual.m_simpleStruct1.FillWithDataset2();

    sw::Serialization serial;
    sw::Serialization deserial;

    serial.SerialOverride()
        .OverrideType< BaseObject >( &OverrideHardcodeDataset );
    deserial.DeserialOverride()
        .OverrideType< BaseObject >( &DeserInPlaceHardcodeDataset);

    REQUIRE_IS_VALID( serial.Serialize( "Serialization/Overrides.Polymorphic.TopLevel.ser", expected ) );
    REQUIRE_IS_VALID( deserial.Deserialize( "Serialization/Overrides.Polymorphic.TopLevel.ser", actual ) );

    CHECK( actual.m_simpleStruct1 == expected.m_simpleStruct1 );
}

// ================================ //
// Serialize dataset number instead of whole structure.
// Test checks, if error will be returned, when user-provided deserialization function attempts
// to create new object instead of using existing one.
TEST_CASE("Serialization.Overrides.Polymorphic.TopLevel.IncorrectOverride", "[Serialization]")
{
    BaseObject expected;
    BaseObject actual;
    expected.m_simpleStruct1.FillWithDataset3();
    actual.m_simpleStruct1.FillWithDataset2();

    sw::Serialization serial;
    sw::Serialization deserial;

    serial.SerialOverride()
        .OverrideType< BaseObject >(&OverrideHardcodeDataset);
    deserial.DeserialOverride()
        .OverrideType< BaseObject >(&DeserOverrideHardcodeDataset);

    REQUIRE_IS_VALID(serial.Serialize("Serialization/Overrides.Polymorphic.TopLevel.IncorrectOverride.ser", expected));
    auto result = deserial.Deserialize("Serialization/Overrides.Polymorphic.TopLevel.IncorrectOverride.ser", actual);
    
    REQUIRE_INVALID(result);
    CHECK(result.GetErrorReason().find("User-provided deserialization override returned new object") != std::string::npos);
}

// ================================ //
// Serialize dataset number instead of whole structure.
// Test checks, if override will be used or default serialization function.
// Here we use polymorphic type serialized as nested object.
TEST_CASE( "Serialization.Overrides.Polymorphic.Nested", "[Serialization]" )
{
    PolymorphicObjectContainer expected;
    PolymorphicObjectContainer actual;
    expected.ObjectPtr = new BaseObject;
    expected.ObjectPtr->m_simpleStruct1.FillWithDataset3();
    // actual ObjectPtr is set to nullptr.
    
    StructWithSimpleTypes referenceStruct;
    referenceStruct.FillWithDataset2();

    sw::Serialization serial;
    sw::Serialization deserial;

    serial.SerialOverride()
        .OverrideType< BaseObject >( &OverrideHardcodeDataset );
    deserial.DeserialOverride()
        .OverrideType< BaseObject >( &DeserOverrideHardcodeDataset );

    REQUIRE_IS_VALID( serial.Serialize( "Serialization/Overrides.Polymorphic.Nested.ser", expected ) );
    REQUIRE_IS_VALID( deserial.Deserialize( "Serialization/Overrides.Polymorphic.Nested.ser", actual ) );

    CHECK( actual.ObjectPtr->m_simpleStruct1 == expected.ObjectPtr->m_simpleStruct1 );
}

// ================================ //
// Serialize dataset number instead of whole structure.
// Test checks, if override will be used or default serialization function.
// Here we use not polymorphic type serialized as nested object.
TEST_CASE( "Serialization.Overrides.NotPolymorphic.Nested", "[Serialization]" )
{
    StructAsRefContainer expected;
    StructAsRefContainer actual;
    expected.SimpleStruct.FillWithDataset3();
    actual.SimpleStruct.FillWithDataset2();     // Change to dataset 2 to see if it worked.

    sw::Serialization serial;
    sw::Serialization deserial;

    serial.SerialOverride()
        .OverrideType< StructWithSimpleTypes >( &OverrideHardcodeDataset );
    deserial.DeserialOverride()
        .OverrideType< StructWithSimpleTypes >( &DeserOverrideHardcodeDatasetStruct );

    REQUIRE_IS_VALID( serial.Serialize( "Serialization/Overrides.NotPolymorphic.Nested.ser", expected ) );
    REQUIRE_IS_VALID( deserial.Deserialize( "Serialization/Overrides.NotPolymorphic.Nested.ser", actual ) );

    CHECK( actual.SimpleStruct == expected.SimpleStruct );
}


