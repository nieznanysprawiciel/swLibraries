#pragma once
/**
@file ProcessorTraits.h
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
class EnableIsProcessor
{};

}	// impl


// ================================ //
//
template< typename VertexType >
class ProcessorTraits : public impl::EnableIsProcessor
{
private:
public:

	typedef VertexType VertexFormat;

};


// ================================ //
//
template< typename Type >
struct isProcessor
{	
	static const bool value = std::is_base_of< impl::EnableIsProcessor, Type >::value;
};



}	// geom
}	// sw

