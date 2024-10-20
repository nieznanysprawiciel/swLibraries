#pragma once
/**
@file StructWithSimpleTypes.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Structs/StructWithSimpleTypes.h"

namespace sw
{

template<typename StructType>
struct TemplateWrapper
{
public:
    StructType		Data;

public:
    TemplateWrapper()
    {
        Data.FillWithDataset1();
    }
};

}	// sw

