#pragma once
/**
@file Serializer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swSerialization/Interfaces/ISerializationContext.h"

#include <string>
#include <assert.h>
#include <memory>




struct SerializerImpl;

/**@brief Writing to file mode.
@ingroup Serialization*/
enum class WritingMode : uint8
{
	Sparing,				///< Mode without spaces and tabulations.
	Readable				///< Mode for reading by people.
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


    /**@brief Writes serialized content to file.
    @todo Consider using filesystem::Path or std::filesystem::path
    @note Not const method. Resets stack. Fix in new implementation.*/
    sw::ReturnResult        SaveFile			( const std::string& fileName, WritingMode mode );

    /**@brief Returns strign with serialized content.
    @todo Could this function fail? Maybe we should use Nullable. But Nullable doesn't support strings yet.
    @note Not const method. Resets stack. Fix in new implementation.*/
    std::string	            SaveString			( WritingMode mode );

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


