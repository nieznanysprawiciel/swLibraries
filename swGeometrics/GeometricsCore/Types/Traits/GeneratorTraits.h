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


namespace impl
{

// ================================ //
//
class EnableIsGenerator
{};

}	// impl


// ================================ //
//
template< typename VertexType, typename IndexType >
class GeneratorTraits : public impl::EnableIsGenerator
{
private:
public:

	typedef VertexType VertexFormat;
	typedef IndexType IndexFormat;

};


// ================================ //
//
template< typename Type >
struct isGenerator
{	
	static const bool value = std::is_base_of< impl::EnableIsGenerator, Type >::value;
};





}	// geom
}	// sw


