#pragma once
/**
@file TypeDescriptor.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swSerialization/Interfaces/Serializer.h"
#include "swSerialization/Interfaces/Deserializer.h"

#include "swSerialization/Serialization/Core/VariantWrapper.h"

#include <functional>




namespace sw
{

struct SerialTypeDesc;
struct DeserialTypeDesc;


typedef std::function< void( ISerializer&, const rttr::instance&, SerialTypeDesc& ) > SerialOverrideFun;
typedef std::function< Nullable< VariantWrapper >( const IDeserializer&, TypeID, rttr::variant&, DeserialTypeDesc& ) > DeserialOverrideFun;



/**@brief Descriptor of type serialization.
@ingroup Serialization*/
struct SerialTypeDesc
{
    typedef SerialOverrideFun OverrideFun;
public:
    std::vector< rttr::property >       Properties;
    SerialOverrideFun                   CustomFunction;
};


/**@brief Descriptor of type deserialization.
@ingroup Serialization*/
struct DeserialTypeDesc
{
    typedef DeserialOverrideFun OverrideFun;
public:
    std::vector< rttr::property >       Properties;
    DeserialOverrideFun                 CustomFunction;
};


}	// sw


