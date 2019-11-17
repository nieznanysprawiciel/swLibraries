#pragma once
/**
@file NodesRegistry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include "swCommonLib/Common/TypesDefinitions.h"

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

#include <vector>


namespace sw
{

namespace impl
{

typedef uint32 NodeIndex;

// ================================ //
//
struct NodeDesc
{
    NodeIndex       Parent;
    NodeIndex       FirstChild;
    NodeIndex       NextSibling;
};


/**@brief Stores mapping of SerialGenerics to internal RapidJSON nodes.*/
class NodesRegistry
{
private:

    std::vector< NodeDesc >             Descriptors;
    std::vector< rapidjson::Value* >    Node;

protected:
public:
    explicit		NodesRegistry		() = default;
                    ~NodesRegistry	    () = default;

public:
};



}   // impl



}	// sw

