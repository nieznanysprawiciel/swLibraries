/**
@file NodesRegistry.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "NodesRegistry.h"


namespace sw::impl
{

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

    return NodePointerImpl( newMemberIdx, parentIdx );
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
        auto childDesc = m_descriptors[ childIdx ];
        childIdx = childDesc.NextSibling;

        if( childDesc.NextSibling == InvalidIndex )
            return {};

        index--;
    }

    return ToNodePtr( NodePointerImpl( childIdx, parentPtr.NodeIdx ) );
}

// ================================ //
//
void                                    NodesRegistry::RegisterChildren     ( NodePointer parent )
{
    NodePointerImpl parentPtr = FromNodePtr( parent );
    auto& parentJsonNode = m_nodes[ parentPtr.NodeIdx ];
    auto& parentDesc = m_descriptors[ parentPtr.NodeIdx ];

    assert( parentJsonNode->IsArray() || parentJsonNode->IsObject() );
    auto size = parentJsonNode->IsArray() ? parentJsonNode->Size() : parentJsonNode->MemberCount();

    // We check if children should be added. It's enought to know that
    // they arent on list when they should. We don't check list correctness,
    // for example: how many nodes there're in comparison to what we expect.
    // All other function should leave registry in correct state.
    if( parentDesc.FirstChild == InvalidIndex && size != 0 )
    {
        if( parentJsonNode->IsArray() )
        {
            for( Size i = 0; i < size; ++i )
            {
                AddMember( parentPtr.NodeIdx, &parentJsonNode[ i ] );
            }
        }
        else    // parentJsonNode->IsObject()
        {
            for( auto& member : parentJsonNode->GetObject() )
            {
                AddMember( parentPtr.NodeIdx, &member.value );
            }
        }
    }
}



}	// sw