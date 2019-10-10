#pragma once
/**
@file ConvertEnums.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/




//====================================================================================//
//			Private	enum helpers
//====================================================================================//

// ================================ //
//
template< typename SrcType >
std::string				Convert::EnumToString		( SrcType value )
{
    static_assert( std::is_enum< SrcType >::value, "Type is not enum" );

    auto type = rttr::type::get< SrcType >();

    assert( type.is_valid() );		/// Type haven't been registered.
    assert( type.is_enumeration() );

    rttr::enumeration enumVal = type.get_enumeration();

    return enumVal.value_to_name( value ).to_string();
}

// ================================ //
//
template< typename DstType >
sw::Nullable< DstType > Convert::StringToEnum		( const std::string& value )
{
    static_assert( std::is_enum< DstType >::value, "Type is not enum" );

    auto type = rttr::type::get< DstType >();

    assert( type.is_valid() );		/// Leave assert, beacause it shouldn't happen.
    if( !type.is_enumeration() )
        return "Type [" + type.get_name().to_string() + "] is not an Enum.";

    rttr::enumeration enumVal = type.get_enumeration();

    rttr::variant result = enumVal.name_to_value( value );

    // Note: Don't return error message. Failing conversion is common thing
    // and we don't want to hurt performance.
    if( !result.is_valid() )
        return ::impl::ConversionException();

    return result.get_value< DstType >();
}



