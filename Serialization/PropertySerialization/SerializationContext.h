#pragma once
/**
@file ISerializationContext.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/Exceptions/Exception.h"

#include "swCommonLib/Serialization/FilePosition.h"
#include "swCommonLib/Serialization/ISerializationContext.h"
#include "swCommonLib/Serialization/PropertySerialization/Core/Exceptions/SerializationException.h"

#include <map>
#include <vector>
#include <type_traits>


namespace sw
{


/**@brief Serialization context for automatic serialization.

You can extend serialization functionality by deriving from this class.

@ingroup Serialization*/
struct SerializationContext : public ISerializationContext
{
private:

	typedef std::map< rttr::type, std::vector< rttr::property > >	TypePropertyMap;
	typedef std::vector< ExceptionPtr >								Exceptions;

public:


	TypePropertyMap			TypeProperties;		///< Maps containing all serializable properties for type.

private:

	Exceptions				m_warnings;

public:
	virtual		~SerializationContext() = default;

public:

	const Exceptions&                   GetWarnings             ();
    void                                AddWarning              ( ExceptionPtr warning );

    template< typename WarningType >
    void                                AddWarning              ( const std::string & message, FilePosition filePos );
};

DEFINE_PTR_TYPE( SerializationContext )




// ========================================================================= //
// Implmentation
// ========================================================================= //

// ***********************
//
template< typename WarningType >
inline void                 SerializationContext::AddWarning	( const std::string& message, FilePosition filePos )
{
    AddWarning( std::make_shared< WarningType >( message, filePos ) );
}

// ***********************
//
template< typename WarningType >
inline void                 Warn                                ( const IDeserializer& deser, const std::string& message )
{
	static_assert( std::is_base_of< SerializationException, WarningType >::value, "WariningType should be derived from SerializationException." );

    auto ctx = deser.GetContext< SerializationContext >();
    if( ctx )
    {
        auto filePos = deser.CurrentLineNumber();

        ctx->AddWarning< WarningType >( message, filePos );
    }
}


}	// sw

