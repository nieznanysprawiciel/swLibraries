#pragma once
/**
@file SerialObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"

#include "ISerializer.h"
#include "FilePosition.h"

#include <string_view>


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
    SerialArray         ArrayView           ();

public:

    /// @name Deserialization API
    /// @{
    Size                                                GetNumElements      () const;
    sw::FilePosition                                    CurrentLineNumber   () const;

    std::pair< std::string_view, SerialGeneric >        GetElement          ( Size index ) const;
    SerialGeneric                                       GetElement          ( std::string_view name ) const;

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




}	// sw


