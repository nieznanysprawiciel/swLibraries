#pragma once
/**
@file Serialzier.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Serialization/ISerializationContext.h"

#include <string>
#include <assert.h>
#include <memory>


/**@defgroup Serialization Serialization
@ingroup CommonLibrary
@brief Automatic serialization library based on rttr properties.*/



struct SerializerImpl;

/**@brief Tryb Zapisywania JSONa.
@ingroup Serialization*/
enum class WritingMode
{
	Sparing,				///< Tryb oszczêdny bez spacji i tabulacji.
	Readable				///< Tryb przeznaczony do czytania przez ludzi.
};

/**@brief Serializers interface.

@ingroup Serialization*/
class ISerializer
{
private:
	SerializerImpl*								impl;
	ISerializationContextPtr					context;
protected:
public:
	explicit	ISerializer		( ISerializationContextPtr serContext );
	virtual		~ISerializer	();

	void		EnterObject		( const std::string& name );
	void		EnterArray		( const std::string& name );

	void		Exit			();

	void		SetAttribute		( const std::string& name, const std::string& value );
	void		SetAttribute		( const std::string& name, const char* value );
	void		SetAttribute		( const std::string& name, uint32 value );
	void		SetAttribute		( const std::string& name, uint64 value );
	void		SetAttribute		( const std::string& name, int32 value );
	void		SetAttribute		( const std::string& name, int64 value );
	void		SetAttribute		( const std::string& name, bool value );
	void		SetAttribute		( const std::string& name, double value );


	bool		SaveFile			( const std::string& fileName, WritingMode mode = WritingMode::Sparing );
	std::string	SaveString			( WritingMode mode = WritingMode::Sparing );


public:

	/**@brief Returns serialization context.

	Check documentation for @ref ISerializationContext for more information.

	Context type is checked only in debug mode (asserts).*/
	template< typename ContextType >
	inline ContextType*			GetContext	()
	{
		assert( context != nullptr );
		
		// Sprawdzanie dynamicznego typu tylko, je¿eli w³¹czone jest RTTI.
#ifdef _CPPRTTI
		assert( typeid( *context ) == typeid( ContextType ) );
#endif

		return static_cast< ContextType* >( context.get() );
	}
};


