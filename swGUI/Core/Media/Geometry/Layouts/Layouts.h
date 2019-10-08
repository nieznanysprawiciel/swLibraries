#pragma once
/**
@file Layouts.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"

#include <string>



namespace sw
{

class InputLayoutDescriptor;
DEFINE_UPTR_TYPE( InputLayoutDescriptor )

}	// sw



namespace sw {
namespace gui
{

// ================================ //
//
template< typename VertexStruct >
InputLayoutDescriptor   		CreateLayoutDescriptor	();

// ================================ //
//
template< typename VertexStruct >
const AssetPath&				GetLayoutName			();


//====================================================================================//
//			Default implementation
//====================================================================================//

// ================================ //
//
template< typename VertexStruct >
InputLayoutDescriptor   		CreateLayoutDescriptor	()
{
	assert( !"Implement me in specializations." );
	return nullptr;
}

// ================================ //
//
template< typename VertexStruct >
const AssetPath&				GetLayoutName			()
{
	assert( !"Implement me in specializations." );
	return "";
}



}	// gui
}	// sw

