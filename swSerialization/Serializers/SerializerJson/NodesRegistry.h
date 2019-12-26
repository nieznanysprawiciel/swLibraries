#pragma once
/**
@file NodesRegistry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swSerialization/Interfaces/SerialObject.h"

#include "swSerialization/External/RapidJSON/include/rapidjson/rapidjson.h"
#include "swSerialization/External/RapidJSON/include/rapidjson/document.h"

#include <vector>
#include <optional>



namespace sw
{

namespace impl
{

typedef uint32 NodeIndex;

const NodeIndex InvalidIndex = std::numeric_limits< NodeIndex >::max();


// ================================ //
//
struct NodeDesc
{
    NodeIndex       Parent;
    NodeIndex       FirstChild;
    NodeIndex       LastChild;
    NodeIndex       NextSibling;

    // ================================ //
    //
    NodeDesc( NodeIndex parent )
        :   Parent( parent )
        ,   FirstChild( InvalidIndex )
        ,   LastChild( InvalidIndex )
        ,   NextSibling( InvalidIndex )
    {}
};

// ================================ //
//
struct NodePointerImpl
{
    NodeIndex       NodeIdx;
    NodeIndex       ParentIdx;

    // ================================ //
    //
    NodePointerImpl( NodeIndex node, NodeIndex parent )
        : NodeIdx( node )
        , ParentIdx( parent )
    {}
};




/**@brief Stores mapping of SerialGenerics to internal RapidJSON nodes.*/
class NodesRegistry
{
private:

    std::vector< NodeDesc >             m_descriptors;
    std::vector< rapidjson::Value* >    m_nodes;
    rapidjson::MemoryPoolAllocator<>&   m_alocator;

protected:
public:
    explicit		NodesRegistry		( rapidjson::Value* root, rapidjson::MemoryPoolAllocator<>& alocator );
                    ~NodesRegistry	    () = default;

public:

    NodePointer             AddObjectMember     ( NodePointer parent, rapidjson::Value&& name, rapidjson::Value&& value );
    NodePointer             AddArrayMember      ( NodePointer parent, rapidjson::Value&& value );

    rapidjson::Value*       GetElement          ( NodePointer nodePtr );

public:

    NodePointerImpl         AddMember           ( NodeIndex parentIdx, rapidjson::Value* newMember );
    NodePointerImpl         AddMember           ( const SerialBase& parent, rapidjson::Value* newMember );

    std::optional< NodePointer >                GetElement      ( NodePointer parent, Size index );

    void                    RegisterChildren    ( NodePointer parent );
    void                    UpdateChildren      ( NodePointer parent );

public:

    static NodePointer      ToNodePtr           ( NodePointerImpl ptrImpl );
    static NodePointerImpl  FromNodePtr         ( NodePointer ptr );
};



}   // impl



}	// sw

