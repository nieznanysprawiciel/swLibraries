#pragma once
/**
@file Convert.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <string>
#include <type_traits>

#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Macros/DefineFmtFormatter.h"
#include "ConvertTraits.h"



/**@brief Errors returned by Convert class.*/
enum class ConversionError : uint8
{
    OutOfRange,                 ///< Source type is out of range of destination type.
    NotConvertible,             ///< Source type can't be convertd to destination.
    FloatTruncation             ///< Can't convert due to precision loss.
};


/**@brief Class for converting to/from string.*/
class Convert
{
private:

	template< typename SrcType >
	static inline std::string			    EnumToString		( SrcType defaultVal );

	template< typename DstType >
	static inline sw::Nullable< DstType >   StringToEnum		( std::string_view value );

public:

	template< typename SrcType >
	static inline typename std::enable_if< std::is_enum< SrcType >::value, std::string >::type
										ToString			( const SrcType& val );

	template< typename DstType >
	static inline DstType               FromString			( std::string_view val, const DstType& defaultValue );

    template< typename DstType >
    static inline sw::Nullable< typename std::enable_if< std::is_enum< DstType >::value, DstType >::type >
                                        FromString			( std::string_view val );

	template< typename SrcType >
	static inline typename std::enable_if< !std::is_enum< SrcType >::value, std::string >::type
										ToString			( const SrcType& val );

    template< typename DstType >
    static inline sw::Nullable< typename std::enable_if< std::is_arithmetic< DstType >::value, DstType >::type >
                                        FromString			( std::string_view val );

    template< typename DstType >
    static inline sw::Nullable< typename std::enable_if< std::is_same< DstType, std::string_view >::value, DstType >::type >
                                        FromString			( std::string_view val )            { return val; }

    template< typename DstType >
    static inline sw::Nullable< typename std::enable_if< is_not_specialized< DstType >::value, DstType >::type >
                                        FromString			( std::string_view val );

    template<>
    static inline typename std::enable_if< !std::is_enum< std::wstring >::value, std::string >::type
										ToString< std::wstring >    ( const std::wstring& value );

	template< typename DstType >
	static inline sw::Nullable< typename std::enable_if< std::is_same< DstType, std::wstring >::value, std::wstring >::type >
										FromString      	        ( std::string_view value );


    template< typename SrcType, typename DstType >
    static inline sw::Result< typename std::enable_if< both_arithmetic< SrcType, DstType >::value, DstType >::type, ConversionError >
                                        FromTo            	        ( const SrcType& val );

    template< typename SrcType, typename DstType >
    static inline sw::Result< typename std::enable_if< is_one_boolean< SrcType, DstType >::value, DstType >::type, ConversionError >
                                        FromTo            	        ( const SrcType& val );

    template< typename SrcType, typename DstType >
    static inline sw::Result< typename std::enable_if< std::is_same< SrcType, DstType >::value, DstType >::type, ConversionError >
                                        FromTo            	        ( const SrcType& val );

    /**@brief Can't convert to std::string_view.*/
    template< typename SrcType, typename DstType >
    static inline sw::Result< typename std::enable_if< std::is_same< DstType, std::string_view >::value, DstType >::type, ConversionError >
                                        FromTo            	        ( const SrcType& val );

public:

    /**@brief Type conversion to string using rttr.*/
    template< typename Type >
    static inline std::string           ToString                    ();

    /**@brief Returns human readable error message retrived from errno.*/
    static std::string                  ErrnoToString               ( int err );
};


namespace sw::impl
{
    sw::ExceptionPtr        ConversionException     ();
}

#include "ConvertArithmetic.h"
#include "ConvertEnums.h"


// ================================ //
//
template< typename SrcType >
inline typename std::enable_if< !std::is_enum< SrcType >::value, std::string >::type
							Convert::ToString		( const SrcType& val )
{
	return std::to_string( val );
}

// ================================ //
//
template< typename DstType >
inline DstType				Convert::FromString		( std::string_view val, const DstType& defaultValue )
{
    auto result = Convert::FromString< DstType >( val );
    
    if( result.IsValid() )
        return result.Get();
    
    return defaultValue;
}

// ================================ //
//
template< typename DstType >
static inline sw::Nullable< typename std::enable_if< is_not_specialized< DstType >::value, DstType >::type >
                            Convert::FromString		( std::string_view val )
{
    static_assert( false, "Specialize template" );
    return sw::impl::ConversionException();
}


//====================================================================================//
//			Public template specialization for enum types
//====================================================================================//

/**@brief Converts enum to string.*/
template< typename SrcType >
inline typename std::enable_if< std::is_enum< SrcType >::value, std::string >::type
							Convert::ToString		( const SrcType& val )
{
	return EnumToString( val );
}

/**@brief Converts string to enum.*/
template< typename DstType >
inline sw::Nullable< typename std::enable_if< std::is_enum< DstType >::value, DstType >::type >
                            Convert::FromString     ( std::string_view val )
{
    return StringToEnum< DstType >( val );
}

//====================================================================================//
//			Wstring to string	
//====================================================================================//

namespace sw::impl
{

std::string                 ConvertWstringToString              ( const std::wstring& value );
std::wstring                ConvertStringToWstring              ( std::string_view value );

}   // impl

// std::codecvt_utf8 deprecated since C++17 without replacement.
#pragma warning( push )
#pragma warning( disable: 4996 )

// ================================ //
//
template<>
static inline typename std::enable_if< !std::is_enum< std::wstring >::value, std::string >::type
							Convert::ToString< std::wstring >   ( const std::wstring& value )
{
    return sw::impl::ConvertWstringToString( value );
}

// ================================ //
//
template< typename SrcType >
inline sw::Nullable< typename std::enable_if< std::is_same< SrcType, std::wstring >::value, std::wstring >::type >
							Convert::FromString             	( std::string_view value )
{
    return sw::impl::ConvertStringToWstring( value );
}

#pragma warning( pop )

//====================================================================================//
//				    Arithemetic types
//====================================================================================//

// ================================ //
//
template< typename DstType >
static inline sw::Nullable< typename std::enable_if< std::is_arithmetic< DstType >::value, DstType >::type >
                            Convert::FromString			( std::string_view val )
{
    return sw::impl::ConvertArithmetic< DstType >( val );
}

//====================================================================================//
//			FromTo conversion	
//====================================================================================//

// ================================ //
//
template< typename SrcType, typename DstType >
inline sw::Result< typename std::enable_if< std::is_same< SrcType, DstType >::value, DstType >::type, ConversionError >
                            Convert::FromTo     ( const SrcType& val )
{
    return val;
}

// ================================ //
//
template< typename SrcType, typename DstType >
static inline sw::Result< typename std::enable_if< std::is_same< DstType, std::string_view >::value, DstType >::type, ConversionError >
                            Convert::FromTo     ( const SrcType& val )
{
    return ConversionError::NotConvertible;
}

//====================================================================================//
//			Type conversion to string	
//====================================================================================//

// ================================ //
//
template< typename Type >
inline std::string          Convert::ToString           ()
{
    return TypeID::get< Type >().get_name().to_string();
}

DEFINE_FMT_FORMATTER( TypeID, "{}", get_name().to_string() );


