#pragma once
/**
@file Default.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


namespace sw {
namespace geom
{

// ================================ //
//
template< typename VertexType >
struct DefaultPositionAcc
{
	static decltype( VertexType::Position )&		Position		( VertexType& vertex ) { return vertex.Position; }
};



}	// geom
}	// sw


