#pragma once
/**
@file SerialArray.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "SerialGeneric.h"

#include "ISerializer.h"
#include "FilePosition.h"



namespace sw
{

class SerialObject;



/**@brief Represents array serialization primitive.

SerialArray API is subset of SerialObject API. Each SerialObject should be convertible
to SerialArray. In some cases (xml) we can't distinguish between array and object on
serializer level. User of this library should be able to use both APIs.

@ingroup Serialization*/
class SerialArray : public impl::SerialBase
{
private:
protected:
public:
    explicit		SerialArray		( ISerializer* ser, impl::NodePointer nodeInternal )
        :   impl::SerialBase( ser, nodeInternal )
    {}
                    ~SerialArray	() = default;
public:

    /// @name Serialization API
    /// Primitives added to array don't have names. We need to be compatibile
    /// with json format. You can extended non generic API to specify name hints.
    /// @{

    SerialObject        AddObject           ();
    SerialArray         AddArray            ();

    /// @}

public:

    /// @name Serialization non generic API
    /// Extended API for serializer specific functionalities.
    /// Don't use if you need generic code that is serializer independent.
    /// @{
    SerialObject        AddObject           ( std::string_view nameHint );
    SerialArray         AddArray            ( std::string_view nameHint );

    void                AddAttribute        ( std::string_view nameHint, std::string_view attribute );

    void                AddAttribute        ( std::string_view nameHint, double attribute );
    void                AddAttribute        ( std::string_view nameHint, uint64 attribute );
    void                AddAttribute        ( std::string_view nameHint, int64 attribute );
    void                AddAttribute        ( std::string_view nameHint, uint32 attribute );
    void                AddAttribute        ( std::string_view nameHint, int32 attribute );
    void                AddAttribute        ( std::string_view nameHint, uint16 attribute );
    void                AddAttribute        ( std::string_view nameHint, int16 attribute );
    void                AddAttribute        ( std::string_view nameHint, uint8 attribute );
    void                AddAttribute        ( std::string_view nameHint, int8 attribute );
    void                AddAttribute        ( std::string_view nameHint, bool attribute );
    void                AddAttribute        ( std::string_view nameHint, char attribute );
    
    /// @}

public:

    /// @name Deserialization API
    /// @{
    Size                        GetNumElements      () const;
    sw::FilePosition            CurrentLineNumber   () const;

    SerialGeneric               GetElement          ( Size index ) const;

    
    /// @}


};


}	// sw
