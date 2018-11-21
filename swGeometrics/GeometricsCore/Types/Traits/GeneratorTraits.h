#pragma once
/**
@file Traits.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <type_traits>


namespace sw {
namespace geom
{


// ================================ //
//
template< typename VertexType, typename IndexType >
class GeneratorTraits
{
private:
public:

	typedef VertexType VertexFormat;
	typedef IndexType IndexFormat;

};


// ================================ //
//
template< typename Type, typename std::enable_if< std::is_base_of< GeneratorTraits< typename Type::VertexFormat, typename Type::IndexFormat >, Type >::value, void >::type* beef = nullptr >
struct isGenerator
{	static const bool value = true;	};

// ================================ //
//
template< typename Type, typename std::enable_if< !std::is_base_of< GeneratorTraits< typename Type::VertexFormat, typename Type::IndexFormat >, Type >::value, void >::type* beef = nullptr > 
struct isGenerator
{	static const bool value = false;	};





}	// geom
}	// sw


