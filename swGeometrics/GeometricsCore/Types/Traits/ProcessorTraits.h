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


// ================================ //
//
template< typename VertexType >
class ProcessorTraits
{
private:
public:

	typedef VertexType VertexFormat;

};


//// ================================ //
////
//template< typename Type, typename std::enable_if_t< !std::is_base_of< ProcessorTraits< typename Type::VertexType >, Type >::value, Type >::type* = nullptr > 
//struct isProcessor
//{	static const bool value = false;	};
//
//// ================================ //
////
//template< typename Type, typename std::enable_if_t< std::is_base_of< ProcessorTraits< typename Type::VertexType >, Type >::value, Type >::type* = nullptr > 
//struct isProcessor
//{	static const bool value = true;	};
//




}	// geom
}	// sw

