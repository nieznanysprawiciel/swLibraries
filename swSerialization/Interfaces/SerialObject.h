#pragma once
/**
@file SerialObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"


namespace sw
{

class SerialArray;


/**@brief Represents object type serialization primitive.

@todo string_view api*/
class SerialObject : public impl::SerialBase
{
private:
protected:
public:
    explicit		SerialObject    () = default;
                    ~SerialObject	() = default;
public:

    /// @name Serialization API
    /// @{

    SerialObject        AddObject           ( const std::string& name );
    SerialArray         AddArray            ( const std::string& name );

    void                AddAttributeString  ( const std::string& name, const std::string& attribute );
    
    void                AddAttributeDouble  ( const std::string& name, double attribute );
    void                AddAttributeUInt64  ( const std::string& name, uint64 attribute );
    void                AddAttributeInt64   ( const std::string& name, int64 attribute );
    void                AddAttributeUInt64  ( const std::string& name, uint32 attribute );
    void                AddAttributeInt64   ( const std::string& name, int32 attribute );
    void                AddAttributeBool    ( const std::string& name, bool attribute );
    void                AddAttributeChar    ( const std::string& name, char attribute );

    /// @}

public:

    /// @name Deserialization API
    /// @{


    /// @}


};



}	// sw


