#pragma once
/**
@file SerialObject.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "SerialGeneric.h"

#include <string_view>


namespace sw
{

class SerialArray;


/**@brief Represents object type serialization primitive.

@ingroup Serialization*/
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

    SerialObject        AddObject           ( std::string_view name );
    SerialArray         AddArray            ( std::string_view name );

    void                AddAttribute        ( std::string_view name, std::string_view attribute );
    
    void                AddAttribute        ( std::string_view name, double attribute );
    void                AddAttribute        ( std::string_view name, uint64 attribute );
    void                AddAttribute        ( std::string_view name, int64 attribute );
    void                AddAttribute        ( std::string_view name, uint32 attribute );
    void                AddAttribute        ( std::string_view name, int32 attribute );
    void                AddAttribute        ( std::string_view name, uint16 attribute );
    void                AddAttribute        ( std::string_view name, int16 attribute );
    void                AddAttribute        ( std::string_view name, uint8 attribute );
    void                AddAttribute        ( std::string_view name, int8 attribute );
    void                AddAttribute        ( std::string_view name, bool attribute );
    void                AddAttribute        ( std::string_view name, char attribute );

    /// @}

public:

    /// @name Deserialization API
    /// @{
    Size                                                GetNumElements      () const;
    sw::FilePosition                                    CurrentLineNumber   () const;

    std::pair< std::string_view, SerialGeneric >        GetElement          ( Size index ) const;
    SerialGeneric                                       GetElement          ( std::string_view name ) const;

    /// @}


};



}	// sw


