#pragma once
/**
@file SerialAttribute.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"



namespace sw
{

/**@brief Represents attribute serialization primitive.
It is one of primitive types: string, number, bool.
@ingroup Serialization*/
class SerialAttribute : public impl::SerialBase
{
private:
protected:
public:
    explicit		SerialAttribute		() = default;
                    ~SerialAttribute	() = default;
public:


};



}	// sw

