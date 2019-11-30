#pragma once
/**
@file SerialGeneric.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "ISerializer.h"

#include <optional>


namespace sw
{

class SerialArray;
class SerialObject;



// ================================ //
//
enum SerialType : int32
{
    Array = 0x01,
    Object = SerialType::Array | 0x10,
    Attribute = 0x1 << 2,

    String = SerialType::Attribute | 0x1 << 3,
    Bool = SerialType::Attribute | 0x1 << 4,
    Character = SerialType::Attribute | 0x1 << 5,
    Number = SerialType::Attribute | 0x1 << 6,

    UInt64 = SerialType::Number | 0x1 << 7,
    Int64 = SerialType::Number | 0x1 << 8,
    Double = SerialType::Number | 0x1 << 9,

    None = 0x1 << 31        ///< Not convertible to anything.
};


namespace impl
{

typedef const void* NodePointer;



/**@brief Base class for serialization nodes.*/
class SerialBase
{
private:
protected:

    ISerializer*        m_serializer;   ///< Serialization interface. @todo We should support here both serializer and deserializer.
    impl::NodePointer   m_node;         ///< Internal implementation specific node pointer. It can be anything.

public:
    explicit		SerialBase		( ISerializer* ser, impl::NodePointer nodeInternal )
        :   m_serializer( ser )
        ,   m_node( nodeInternal )
    {}
                    ~SerialBase	    () = default;
public:

    /**@brief Gets pointer to serializer internal representation of node.*/
    impl::NodePointer   GetNodePtr  () const { return m_node; }
};


}   // impl



/**@brief Generic serialization node.

This class and all Serial* classes implement serialization interface
of single node. They are only light wrappers for real serializer implementation
and they only forward calls.

@ingroup Serialization*/
class SerialGeneric : public impl::SerialBase
{
private:
protected:

    SerialType          m_type;

public:
    explicit		SerialGeneric	( ISerializer* ser, impl::NodePointer nodeInternal, SerialType type )
        :   impl::SerialBase( ser, nodeInternal )
        ,   m_type( type )
    {}
                    ~SerialGeneric	() = default;
public:

    SerialType          GetSerialType   () const { return m_type; }

    bool                IsArray         () const { return IsArray( m_type ); }
    bool                IsObject        () const { return IsObject( m_type ); }
    bool                IsAttribute     () const { return IsAttribute( m_type ); }

    std::optional< SerialObject >       ObjectView      ();
    std::optional< SerialArray >        ArrayView       ();
    std::optional< SerialAttribute >    AttributeView   ();

public:

    static bool         IsArray         ( SerialType type );
    static bool         IsObject        ( SerialType type );
    static bool         IsAttribute     ( SerialType type );
};


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
inline bool             SerialGeneric::IsArray      ( SerialType type )
{
    return ( type & SerialType::Array ) == SerialType::Array;
}

// ================================ //
//
inline bool             SerialGeneric::IsObject     ( SerialType type )
{
    return ( type & SerialType::Object ) == SerialType::Object;
}

// ================================ //
//
inline bool             SerialGeneric::IsAttribute  ( SerialType type )
{
    return ( type & SerialType::Attribute ) == SerialType::Attribute;
}


}	// sw


