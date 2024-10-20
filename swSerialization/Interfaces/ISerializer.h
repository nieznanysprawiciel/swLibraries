#pragma once
/**
@file ISerializer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "ISerializationContext.h"
#include "FilePosition.h"

#include <optional>
#include <string_view>


namespace sw
{

class SerialArray;
class SerialObject;
class SerialAttribute;
class SerialGeneric;


typedef std::pair< std::string_view, SerialGeneric > SerialObjectChild;


/**@brief Mode of writing serialization content.
@ingroup Serialization*/
enum class WritingMode : uint8
{
    Sparing,				///< Mode without spaces and tabulations.
    Readable				///< Mode for reading by people.
};




/**@brief Interface for both serialization and deserialization.

@ingroup Serialization*/
class ISerializer
{
    friend class SerialObject;
    friend class SerialArray;

private:
protected:

    ISerializationContextPtr        m_context;

public:
    explicit		ISerializer		( ISerializationContextPtr serContext )
        : m_context( serContext ) {}

    virtual         ~ISerializer	() = default;

public:

    /**@brief Writes serialized content to file.
    @todo Consider using filesystem::Path or std::filesystem::path*/
    virtual ReturnResult		SaveFile			( const std::string& fileName, WritingMode mode = WritingMode::Sparing ) const = 0;

    /**@brief Returns strign with serialized content.
    @todo Could this function fail? Maybe we should use Nullable. But Nullable doesn't support strings yet.*/
    virtual std::string	        SaveString			( WritingMode mode = WritingMode::Sparing ) const = 0;

    /**@brief Loads content of file to this serializer.
    @todo Consider using filesystem::Path or std::filesystem::path*/
    virtual ReturnResult        LoadFromFile	    ( const std::string& fileName ) = 0;

    /**@brief Deserializes content of string.
    Insitu parsing of string.*/
    virtual ReturnResult        LoadFromString	    ( std::string content ) = 0;

    /**@brief Gets serialization root object.*/
    virtual SerialObject        Root                () = 0;

protected:

    /// @name Serialization API
    /// @{

    virtual SerialObject        AddObject           ( const SerialObject& parent, std::string_view name ) = 0;
    virtual SerialArray         AddArray            ( const SerialObject& parent, std::string_view name ) = 0;

    /**@brief Adds serialization node to array.
    nameHint is optional, not all serializers will support it.*/
    virtual SerialObject        AddObject           ( const SerialArray& parent, std::string_view nameHint ) = 0;
    virtual SerialArray         AddArray            ( const SerialArray& parent, std::string_view nameHint ) = 0;

    virtual void                AddAttribute        ( const SerialObject& parent, std::string_view name, std::string_view attribute ) = 0;
    virtual void                AddAttribute        ( const SerialObject& parent, std::string_view name, double attribute ) = 0;
    virtual void                AddAttribute        ( const SerialObject& parent, std::string_view name, uint64 attribute ) = 0;
    virtual void                AddAttribute        ( const SerialObject& parent, std::string_view name, int64 attribute ) = 0;
    virtual void                AddAttribute        ( const SerialObject& parent, std::string_view name, bool attribute ) = 0;
    virtual void                AddAttribute        ( const SerialObject& parent, std::string_view name, char attribute ) = 0;

    /// @}

public:

    /// @name Deserialization API
    /// @{

    virtual Size                                        GetNumElements      ( const SerialObject& parent ) const = 0;
    virtual sw::FilePosition                            CurrentLineNumber   ( const SerialObject& node ) const = 0;

    virtual std::optional< SerialObjectChild >          GetElement          ( const SerialObject& parent, Size index ) const = 0;
    virtual std::optional< SerialGeneric >              GetElement          ( const SerialObject& parent, std::string_view name ) const = 0;

    virtual std::string_view                            GetString           ( const SerialAttribute& attribute ) const = 0;
    virtual double                                      GetDouble           ( const SerialAttribute& attribute ) const = 0;
    virtual uint64                                      GetUInt64           ( const SerialAttribute& attribute ) const = 0;
    virtual int64                                       GetInt64            ( const SerialAttribute& attribute ) const = 0;
    virtual bool                                        GetBool             ( const SerialAttribute& attribute ) const = 0;

    /// @}

public:

    /**@brief Returns serialization context.

    Check documentation for @ref ISerializationContext for more information.

    Context type is checked only in debug mode (asserts).*/
    template< typename ContextType >
    inline ContextType*         GetContext	        () const
    {
        assert( m_context != nullptr );

        // Sprawdzanie dynamicznego typu tylko, je¿eli w³¹czone jest RTTI.
#ifdef _CPPRTTI
        assert( typeid( *m_context ) == typeid( ContextType ) );
#endif

        return static_cast< ContextType* >( m_context.get() );
    }
};

DEFINE_OPTR_TYPE( ISerializer );


}	// sw

