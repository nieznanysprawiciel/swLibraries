#include "swGUI/TestFramework/stdafx.h"
#include "TesterBinding.h"



namespace sw {
namespace gui
{

// ================================ //
//
rttr::variant			MockConverter::Convert		( const rttr::variant& object, TypeID targetType, const rttr::variant& params, const CultureInfo* culture ) const
{
	assert( !"Implement me" );
	return rttr::variant();
}

// ================================ //
//
rttr::variant			MockConverter::ConvertBack	( const rttr::variant& object, TypeID targetType, const rttr::variant& params, const CultureInfo* culture ) const
{
	assert( !"Implement me" );
	return rttr::variant();
}

// ================================ //
//
bool					MockConverter::CanConvert		( TypeID srcType, TypeID targetType ) const
{
	return m_forwardConversion;
}

// ================================ //
//
bool					MockConverter::CanConvertBack	( TypeID srcType, TypeID targetType ) const
{
	return m_backwardConversion;
}

}	// gui
}	// sw
