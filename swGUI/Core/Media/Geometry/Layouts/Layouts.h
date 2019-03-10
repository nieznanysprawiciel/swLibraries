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
InputLayoutDescriptorUPtr		CreateLayoutDescriptor	();

// ================================ //
//
template< typename VertexStruct >
const std::wstring&				GetLayoutName			();

// ================================ //
//
template< typename VertexStruct >
std::string						GetLayoutExampleShader	();


//====================================================================================//
//			Default implementation
//====================================================================================//

// ================================ //
//
template< typename VertexStruct >
InputLayoutDescriptorUPtr		CreateLayoutDescriptor	()
{
	assert( !"Implement me in specializations." );
	return nullptr;
}

// ================================ //
//
template< typename VertexStruct >
const std::wstring&				GetLayoutName			()
{
	assert( !"Implement me in specializations." );
	return L"";
}

// ================================ //
//
template< typename VertexStruct >
std::string						GetLayoutExampleShader	()
{
	assert( !"Implement me in specializations." );
	return "";
}


}	// gui
}	// sw

