#pragma once
/**
@file SerialObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"

#include "ISerializer.h"
#include "FilePosition.h"

#include "swCommonLib/Common/Exceptions/Result.h"

#include <string_view>
#include <optional>


namespace sw
{

class SerialArray;


/**@brief Represents object type serialization primitive.

@ingroup Serialization*/
class SerialObject : public impl::SerialBase
{
private:
protected:
public:
    explicit		SerialObject    ( sw::ISerializer* ser, impl::NodePointer nodeInternal )
        :   impl::SerialBase( ser, nodeInternal )
    {}
                    ~SerialObject	() = default;
public:

    /// @name Serialization API
    /// @{

    SerialObject        AddObject           ( std::string_view name );
    SerialArray         AddArray            ( std::string_view name );

    /**@brief This function catches string literals, that otherwise would be implicite converted to bool.*/
    void                AddAttribute        ( std::string_view name, const char* attribute );
    void                AddAttribute        ( std::string_view name, std::string_view attribute );
    
    void                AddAttribute        ( std::string_view name, double attribute );
    void                AddAttribute        ( std::string_view name, uint64 attribute );
    void                AddAttribute        ( std::string_view name, int64 attribute );
    void                AddAttribute        ( std::string_view name, uint32 attribute );
    void                AddAttribute        ( std::string_view name, int32 attribute );
    void                AddAttribute        ( std::string_view name, uint16 attribute );
    void                AddAttribute        ( std::string_view name, int16 attribute );
    void                AddAttribute        ( std::string_view name, uint8 attribute );
    void                AddAttribute        ( std::string_view name, int8 attribute );
    void                AddAttribute        ( std::string_view name, bool attribute );
    void                AddAttribute        ( std::string_view name, char attribute );

    /// @}

    /**@brief Cast SerialObject to SerialArray. Array API can represent Object.*/
    SerialArray         ArrayView           () const;

public:

    /// @name Deserialization API
    /// @{
    Size                                        GetNumElements      () const;
    sw::FilePosition                            CurrentLineNumber   () const;

    std::optional< SerialObjectChild >          GetElement          ( Size index ) const;

    /**@brief Returns element of given name.
    This can be either child node or attribute. Only first occurance of this name is returned.*/
    std::optional< SerialGeneric >              GetElement          ( std::string_view name ) const;

    /**@brief Helper functions that allow to omit SerialGeneric interface and get expected
    typed interface. This way there's only one optional dispatching instead of two.*/
    Result< SerialArray, SerialError >          GetArray            ( std::string_view name ) const;
    Result< SerialArray, SerialError >          GetArray            ( Size index ) const;

    Result< SerialObject, SerialError >         GetObject           ( std::string_view name ) const;
    Result< SerialObject, SerialError >         GetObject           ( Size index ) const;

    Result< SerialAttribute, SerialError >      GetAttribute        ( std::string_view name ) const;
    Result< SerialAttribute, SerialError >      GetAttribute        ( Size index ) const;
    /// @}

public:    
};

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline SerialObject             SerialObject::AddObject     ( std::string_view name )
{
    return m_serializer->AddObject( *this, name );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, std::string_view attribute )
{
    m_serializer->AddAttribute( *this, name, attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, const char* attribute )
{
    m_serializer->AddAttribute( *this, name, std::string_view( attribute ) );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, double attribute )
{
    m_serializer->AddAttribute( *this, name, attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, uint64 attribute )
{
    m_serializer->AddAttribute( *this, name, attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, int64 attribute )
{
    m_serializer->AddAttribute( *this, name, attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, uint32 attribute )
{
    m_serializer->AddAttribute( *this, name, (uint64)attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, int32 attribute )
{
    m_serializer->AddAttribute( *this, name, (int64)attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, uint16 attribute )
{
    m_serializer->AddAttribute( *this, name, (uint64)attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, int16 attribute )
{
    m_serializer->AddAttribute( *this, name, (int64)attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, uint8 attribute )
{
    m_serializer->AddAttribute( *this, name, (uint64)attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, int8 attribute )
{
    m_serializer->AddAttribute( *this, name, (int64)attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, bool attribute )
{
    m_serializer->AddAttribute( *this, name, attribute );
}

// ================================ //
//
inline void                     SerialObject::AddAttribute  ( std::string_view name, char attribute )
{
    m_serializer->AddAttribute( *this, name, attribute );
}

//====================================================================================//
//			Deserialization API
//====================================================================================//

// ================================ //
//
inline std::optional< SerialGeneric >       SerialObject::GetElement    ( std::string_view name ) const
{
    return m_serializer->GetElement( *this, name );
}

}	// sw


