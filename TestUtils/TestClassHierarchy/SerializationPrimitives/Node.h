#pragma once

#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"

#include <random>
#include <vector>


namespace sw
{

class Node;


// ================================ //
//
class Node
{
public:

	std::vector< Node >		Children;
	EngineObject*			Generic;

public:

	// ================================ //
	//
	explicit			Node()
		: Generic( nullptr )
	{}

	// ================================ //
	//
	~Node()
	{
		delete  Generic;
	}

	// ================================ //
	//
	void		GenerateTree		( uint64 numNodes, uint64 depth, TypeID genericToCreate );


};

//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
inline void			Node::GenerateTree			( uint64 numNodes, uint64 nodesOnLevel, TypeID genericToCreate )
{
	Generic = genericToCreate.create().get_value< EngineObject* >();

	if( numNodes > 0 )
	{
		Children.clear();

		nodesOnLevel = numNodes < nodesOnLevel ? numNodes : nodesOnLevel;
		numNodes -= nodesOnLevel;

		auto nodesInSubtree = numNodes / nodesOnLevel;
		auto rest = numNodes % nodesOnLevel;

		Children.resize( nodesOnLevel );

		for( uint64 nodeIdx = 0; nodeIdx < nodesOnLevel; nodeIdx++ )
		{
			auto& node = Children[ nodeIdx ];

			auto nodeToGen = rest-- > 0 ? nodesInSubtree + 1 : nodesInSubtree;
			node.GenerateTree( nodeToGen, nodesOnLevel, genericToCreate );
		}
	}
}


}	// sw

