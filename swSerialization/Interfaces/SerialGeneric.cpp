/**
@file SerialGeneric.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"

#include "SerialArray.h"
#include "SerialObject.h"




namespace sw
{

// ================================ //
//
std::optional< SerialObject >           SerialGeneric::ObjectView   ()
{
    if( IsObject() )
        return SerialObject( m_serializer, m_node );
    return {};
}

// ================================ //
//
std::optional< SerialArray >            SerialGeneric::ArrayView    ()
{
    if( IsArray() )
        return SerialArray( m_serializer, m_node );
    return {};
}

}	// sw


