#pragma once
/**
@file SerialGeneric.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "ISerializer.h"


namespace sw
{





// ================================ //
//
enum SerialType
{
    Object,
    Array,
    Attribute,

    String,
    Bool,
    Character,
    Number,

    UInt64,
    Int64,
    UInt32,
    Int32,
    Double
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

    bool                IsArray         () const { return m_type | SerialType::Array; }
    bool                IsObject        () const { return m_type | SerialType::Object; }
    bool                IsAttribute     () const;
};



}	// sw


