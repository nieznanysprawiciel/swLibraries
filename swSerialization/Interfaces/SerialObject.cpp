/**
@file SerialObject.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialObject.h"
#include "SerialArray.h"



namespace sw
{


// ================================ //
//
SerialArray             SerialObject::AddArray      ( std::string_view name )
{
    return m_serializer->AddArray( *this, name );
}

// ================================ //
//
SerialArray             SerialObject::ArrayView     () const
{
    return SerialArray( m_serializer, m_node );
}


}	// sw


