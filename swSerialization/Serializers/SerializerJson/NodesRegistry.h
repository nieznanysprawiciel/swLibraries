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


namespace sw
{

namespace impl
{

typedef uint32 NodeIndex;

extern const NodeIndex InvalidIndex;


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


    std::pair< std::string_view, NodePointer >          GetElement      ( NodePointer parent, Size index );
    NodePointer                                         GetElement      ( NodePointer parent, std::string_view name );

public:

    NodePointerImpl         AddMember           ( NodeIndex parentIdx, rapidjson::Value* newMember );
    NodePointerImpl         AddMember           ( const SerialBase& parent, rapidjson::Value* newMember );


public:

    static NodePointer      ToNodePtr           ( NodePointerImpl ptrImpl );
    static NodePointerImpl  FromNodePtr         ( NodePointer ptr );
};



}   // impl



}	// sw
