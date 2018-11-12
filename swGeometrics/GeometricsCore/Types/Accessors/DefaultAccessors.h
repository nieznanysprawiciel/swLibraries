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
	static decltype( VertexType::Position )&		Get				( VertexType& vertex ) { return vertex.Position; }
};

// ================================ //
//
template< typename VertexType >
struct DefaultUVAcc
{
	static decltype( VertexType::UV )&				Get				( VertexType& vertex ) { return vertex.UV; }
};

}	// geom
}	// sw


