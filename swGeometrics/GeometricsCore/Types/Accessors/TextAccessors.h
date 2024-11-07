#pragma once
/**
@file TextAccessors.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


namespace sw {
namespace geom
{

/**@brief Accessor for VertexType using single UVs coords fields.*/
template< typename VertexType >
struct TextAcc
{
	static decltype(VertexType::Position)&		GetPos				( VertexType& vertex ) { return vertex.Position; }
	static decltype(VertexType::UV)&			GetUV				( VertexType& vertex ) { return vertex.UV; }
};

/**@brief Accessor for Text vertex supporting texturing, what requires 2 fields for UVs
- one for TextAtlas
- second for additional texture*/
template< typename VertexType >
struct TexturedTextAcc
{
	static decltype(VertexType::Position)&		GetPos				( VertexType& vertex ) { return vertex.Position; }
	static decltype(VertexType::AtlasCoords)&	GetUV				( VertexType& vertex ) { return vertex.AtlasCoords; }
};


}	// geom
}	// sw


