#pragma once
/**
@file Overrides.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "TypeDescriptor.h"
#include "swSerialization/Serialization/SerializationTypes.h"


namespace sw
{

/**@brief Defines serialization overrides for chosen types.

If you don't override serialization for some type, default function will be used.
It is recomended to override types only if necessary. You avoid the need to test your code.

Remember that order of calls to Override* functions matters. Second call will overwrite previously
set function. It's useful in large hierarchies. You can first override function for some base class
and than set more specific function for derived classes.

@ingroup Serialization*/
template< typename DescriptorType >
class Overrides
{
    typedef std::map< rttr::type, DescriptorType > TypeOverridesMap;
    typedef typename DescriptorType::OverrideFun OverrideFun;

    typedef Overrides< DescriptorType > Self;
private:

    TypeOverridesMap        m_overridesDescs;

protected:
public:
    explicit		Overrides		() = default;
                    ~Overrides	    () = default;

public:

    /**@brief Returns type descriptor.
    Properties will be added, if descriptor didn't existed before.*/
    DescriptorType      GetTypeDescriptor           ( rttr::type objType );

    /**@brief Overrides default serialization for selected type only.*/
    Self&               OverrideType                ( rttr::type objType, OverrideFun function );

    /**@brief Create object type from template argument.*/
    template< typename Type >
    Self&               OverrideType                ( OverrideFun function );

    /**@brief Overrides default serialization for selected type and all derived types.*/
    Self&               OverrideDerived             ( rttr::type objType, OverrideFun function );

    /**@brief Create object type from template argument.*/
    template< typename Type >
    Self&               OverrideDerived             ( OverrideFun function );

private:

    std::vector< rttr::property >       ListFilteredProperties      ( rttr::type objType );
    bool                                ShouldSerialize             ( rttr::property prop );
};


typedef Overrides< DeserialTypeDesc > OverridesDeserial;
typedef Overrides< SerialTypeDesc > OverridesSerial;


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< typename DescriptorType >
inline auto Overrides< DescriptorType >::GetTypeDescriptor
(
    rttr::type objType
) -> DescriptorType
{
    objType = objType.get_raw_type();

    auto iter = m_overridesDescs.find( objType );
    if( iter == m_overridesDescs.end() )
    {
        DescriptorType& typeDesc = m_overridesDescs[ objType ];
        typeDesc.Properties = ListFilteredProperties( objType );

        return typeDesc;
    }
    return iter->second;
}

// ================================ //
//
template< typename DescriptorType >
inline auto Overrides< DescriptorType >::OverrideType
(
    rttr::type objType,
    OverrideFun function
) -> Self&
{
    objType = objType.get_raw_type();

    DescriptorType& desc = m_overridesDescs[ objType ];

    // We must fill full descriptor. There's no way to tell, if properties
    // were already listed or not. If descriptor exist, properties must exist.
    desc.CustomFunction = function;
    desc.Properties = ListFilteredProperties( objType );
    
    return *this;
}

// ================================ //
//
template< typename DescriptorType >
inline auto Overrides< DescriptorType >::OverrideDerived
(
    rttr::type objType,
    OverrideFun function
) -> Self&
{
    objType = objType.get_raw_type();

    OverrideType( objType, function );
    
    auto derivedVec = objType.get_derived_classes();
    for( auto derivedType : derivedVec )
    {
        OverrideDerived( derivedType, function );
    }

    return *this;
}

// ================================ //
//
template< typename DescriptorType >
inline auto Overrides< DescriptorType >::ListFilteredProperties
(
    rttr::type objType
) -> std::vector< rttr::property >
{
    std::vector< rttr::property > propVec;
    auto properties = objType.get_properties();

    for( auto& property : properties )
    {
        if( ShouldSerialize( property ) )
            propVec.push_back( property );
    }

    return propVec;
}

// ================================ //
//
template< typename DescriptorType >
auto Overrides< DescriptorType >::ShouldSerialize
(
    rttr::property prop
) -> bool
{
    auto saveFlagMeta = prop.get_metadata( SerializationMeta::Serialize );

    // If there's no metadata - serialize by default.
    if( !saveFlagMeta.is_valid() )
        return true;

    // If type of metadata is not bool, probably someone used this flag in other context than serialization??
    assert( saveFlagMeta.is_type< bool >() );
    if( !saveFlagMeta.is_type< bool >() )
        return false;

    return saveFlagMeta.get_value< bool >();
}

// ================================ //
//
template< typename DescriptorType >
template< typename Type >
inline auto Overrides< DescriptorType >::OverrideType
(
    OverrideFun function
) -> Self&
{
    return OverrideType( TypeID::get< Type >(), function );
}

// ================================ //
//
template< typename DescriptorType >
template< typename Type >
inline auto Overrides< DescriptorType >::OverrideDerived
(
    OverrideFun function
) -> Self&
{
    return OverrideDerived( TypeID::get< Type >(), function );
}

}	// sw


