#pragma once
/**
@file Convert.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <string>
#include <codecvt>
#include <type_traits>

#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "ConvertTraits.h"




/**@brief Class for converting to/from string.*/
class Convert
{
private:

	template< typename SrcType >
	static inline std::string			    EnumToString		( SrcType defaultVal );

	template< typename DstType >
	static inline sw::Nullable< DstType >   StringToEnum		( const std::string& value );

public:

	template< typename SrcType >
	static inline typename std::enable_if< std::is_enum< SrcType >::value, std::string >::type
										ToString			( const SrcType& val );

	template< typename DstType >
	static inline DstType               FromString			( const std::string& val, const DstType& defaultValue );

    template< typename DstType >
    static inline sw::Nullable< typename std::enable_if< std::is_enum< DstType >::value, DstType >::type >
                                        FromString			( const std::string& val );

	template< typename SrcType >
	static inline typename std::enable_if< !std::is_enum< SrcType >::value, std::string >::type
										ToString			( const SrcType& val );

    template< typename DstType >
    static inline sw::Nullable< typename std::enable_if< std::is_arithmetic< DstType >::value, DstType >::type >
                                        FromString			( const std::string& val );

    template< typename DstType >
    static inline sw::Nullable< typename std::enable_if< is_not_specialized< DstType >::value, DstType >::type >
                                        FromString			( const std::string& val );

    template<>
    static inline typename std::enable_if< !std::is_enum< std::wstring >::value, std::string >::type
										ToString< std::wstring >    ( const std::wstring& value );

	template< typename DstType >
	static inline sw::Nullable< typename std::enable_if< std::is_same< DstType, std::wstring >::value, std::wstring >::type >
										FromString      	        ( const std::string& value );

};


namespace impl
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
inline DstType				Convert::FromString		( const std::string& val, const DstType& defaultValue )
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
                            Convert::FromString		( const std::string& val )
{
    static_assert( false, "Specialize template" );
    return ::impl::ConversionException();
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
                            Convert::FromString     ( const std::string& val )
{
    return StringToEnum< DstType >( val );
}

//====================================================================================//
//			Wstring to string	
//====================================================================================//

// ================================ //
//
template<>
static inline typename std::enable_if< !std::is_enum< std::wstring >::value, std::string >::type
							Convert::ToString< std::wstring >   ( const std::wstring& value )
{
	typedef std::codecvt_utf8< wchar_t > convert_type;
	std::wstring_convert< convert_type, wchar_t > converter;
	return converter.to_bytes( value );
}

// ================================ //
//
template< typename SrcType >
inline sw::Nullable< typename std::enable_if< std::is_same< SrcType, std::wstring >::value, std::wstring >::type >
							Convert::FromString             	( const std::string& value )
{
	typedef std::codecvt_utf8< wchar_t > convert_type;
	std::wstring_convert< convert_type, wchar_t > converter;
	return converter.from_bytes( value );
}

//====================================================================================//
//				    Arithemetic types
//====================================================================================//

// ================================ //
//
template< typename DstType >
static inline sw::Nullable< typename std::enable_if< std::is_arithmetic< DstType >::value, DstType >::type >
                            Convert::FromString			( const std::string& val )
{
    return ::impl::ConvertArithmetic< DstType >( val );
}




