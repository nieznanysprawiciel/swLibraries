/**
@file NodesRegistry.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "NodesRegistry.h"


namespace sw::impl
{

const NodeIndex InvalidIndex = std::numeric_limits< NodeIndex >::max();


// ================================ //
//
NodePointer             NodesRegistry::ToNodePtr       ( NodePointerImpl ptrImpl )
{
    return *reinterpret_cast< NodePointer* >( &ptrImpl );
}

// ================================ //
//
NodePointerImpl         NodesRegistry::FromNodePtr     ( NodePointer ptr )
{
    return *reinterpret_cast< NodePointerImpl* >( &ptr );
}



// ================================ //
//
NodesRegistry::NodesRegistry                                ( rapidjson::Value* root, rapidjson::MemoryPoolAllocator<>& alocator )
    : m_alocator( alocator )
{
    m_nodes.push_back( root );
    m_descriptors.push_back( NodeDesc( InvalidIndex ) );
}

// ================================ //
//
NodePointer             NodesRegistry::AddObjectMember      ( NodePointer parent, rapidjson::Value&& name, rapidjson::Value&& value )
{
    auto& parentJsonNode = *GetElement( parent );

    auto numMembers = parentJsonNode.Size();
    parentJsonNode.AddMember( std::move( name ), std::move( value ), m_alocator );
    
    // Get added member.
    auto newNodeIdx = parentJsonNode.MemberCount() - 1;

    return ToNodePtr( AddMember( FromNodePtr( parent ).NodeIdx, &parentJsonNode[ newNodeIdx ] ) );
}

// ================================ //
//
NodePointerImpl         NodesRegistry::AddMember            ( NodeIndex parentIdx, rapidjson::Value* newMember )
{
    // This should always be true. Check to be sure everything is correct.
    assert( m_nodes.size() == m_descriptors.size() );

    NodeIndex newMemberIdx = (NodeIndex)m_nodes.size();
    m_nodes.push_back( newMember );
    m_descriptors.push_back( NodeDesc( parentIdx ) );

    // Update information in parent.
    auto& parent = m_descriptors[ parentIdx ];
    
    if( parent.LastChild == InvalidIndex )
    {
        // We don't have children on list.
        assert( parent.FirstChild == InvalidIndex );
        
        parent.FirstChild = newMemberIdx;
        parent.LastChild = newMemberIdx;
    }
    else
    {
        // We already had children.
        auto prevSiblingIdx = parent.LastChild;

        assert( prevSiblingIdx < m_descriptors.size() );
        auto& prevSibling = m_descriptors[ prevSiblingIdx ];
        
        parent.LastChild = newMemberIdx;
        prevSibling.NextSibling = newMemberIdx;
    }

    return NodePointerImpl( parentIdx, newMemberIdx );
}

// ================================ //
//
NodePointerImpl         NodesRegistry::AddMember            ( const SerialBase& parent, rapidjson::Value* newMember )
{
    return AddMember( FromNodePtr( parent.GetNodePtr() ).NodeIdx, newMember );
}

// ================================ //
//
NodePointer             NodesRegistry::AddArrayMember       ( NodePointer parent, rapidjson::Value&& value )
{
    return NodePointer();
}

// ================================ //
//
rapidjson::Value*       NodesRegistry::GetElement           ( NodePointer nodePtr )
{
    NodePointerImpl parentPtr = FromNodePtr( nodePtr );
    
    if( parentPtr.NodeIdx < m_nodes.size() )
        return m_nodes[ parentPtr.NodeIdx ];
    return nullptr;
}

//====================================================================================//
//			Deserialization api	
//====================================================================================//

// ================================ //
//
std::optional< NodePointer >            NodesRegistry::GetElement           ( NodePointer parent, Size index )
{
    auto parentPtr = FromNodePtr( parent );
    auto& parentDesc = m_descriptors[ parentPtr.NodeIdx ];

    if( parentDesc.FirstChild == InvalidIndex )
        return {};

    auto childIdx = parentDesc.FirstChild;
    while( index > 0 )
    {
        auto childDesc = m_descriptors[ parentDesc.FirstChild ];
        childIdx = childDesc.NextSibling;

        if( childDesc.NextSibling == InvalidIndex )
            return {};
    }

    return ToNodePtr( NodePointerImpl( childIdx, parentPtr.NodeIdx ) );
}



}	// sw