#pragma once
/**
@file ResourcePtr.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include <type_traits>

// Included to register wrapper_mapper in rttr
#include "swCommonLib/Reflection/src/rttr/wrapper_mapper.h"


namespace sw
{


class Resource;


/**@brief Wrapper for low level resources and high level assets.

This class automatically increments and decrements resources and assets reference counter.
Notice that it's not equivalent of std::shared_ptr. When references counter reaches 0, resource won't be released.
@ref AssetsManager is the only one owner of resource and it's responsibility is, to destroy resource
when it's needed. Even when there's no Actor in engine that uses it, resource can still remain for future use.

@ingroup Resources*/
template< typename ResourceType >
class ResourcePtr
{
private:

	ResourceType*		m_resource;

public:

	explicit			ResourcePtr		();
						ResourcePtr		( ResourceType* ptr );
						ResourcePtr		( const ResourcePtr& other );
						ResourcePtr		( ResourcePtr&& other );

						~ResourcePtr	();
public:
	
	void				operator=			( ResourceType* ptr );
	void				operator=			( const ResourcePtr< ResourceType >& ptr );
	ResourceType*		operator*			();
	ResourceType*		operator->			();
	const ResourceType* operator*			() const;
	const ResourceType* operator->			() const;
						operator void*		() const;

	void				ReleaseResource		();
	void				AssignPointer		( ResourceType* ptr );

	ResourceType*		Ptr					() const;

};

#define DEFINE_RESOURCE_PTR_TYPE( type )			typedef ResourcePtr< type > type ## Ptr;


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename ResourceType >
inline ResourcePtr< ResourceType >::ResourcePtr		()
{
	static_assert( std::is_base_of< Resource, ResourceType >::value, "Template parameter type must inherit from Resource" );
	m_resource = nullptr;
}

// ================================ //
//
template< typename ResourceType >
inline ResourcePtr< ResourceType >::ResourcePtr		( ResourceType* ptr )
	: m_resource( nullptr )
{
	static_assert( std::is_base_of< Resource, ResourceType >::value, "Template parameter type must inherit from Resource" );
	AssignPointer( ptr );
}

// ================================ //
//
template< typename ResourceType >
inline ResourcePtr< ResourceType >::~ResourcePtr	()
{
	ReleaseResource();
}

// ================================ //
//
template< typename ResourceType >
inline ResourcePtr< ResourceType >::ResourcePtr		( const ResourcePtr& other )
{
	m_resource = nullptr;
	AssignPointer( other.m_resource );
}

// ================================ //
//
template< typename ResourceType >
inline ResourcePtr< ResourceType >::ResourcePtr		( ResourcePtr&& other )
{
	if( this != &other )
	{
		m_resource = other.m_resource;
		other.m_resource = nullptr;
	}
}

// ================================ //
//
template< typename ResourceType >
void					ResourcePtr< ResourceType >::operator=			( ResourceType* ptr )
{
	ReleaseResource();
	AssignPointer( ptr );
}

// ================================ //
//
template< typename ResourceType >
void					ResourcePtr< ResourceType >::operator=			( const ResourcePtr< ResourceType >& ptr )
{
	ReleaseResource();
	AssignPointer( ptr.m_resource );
}

// ================================ //
//
template< typename ResourceType >
inline					ResourcePtr< ResourceType >::operator void*		() const
{
	return m_resource;
}

// ================================ //
//
template< typename ResourceType >
ResourceType*			ResourcePtr< ResourceType >::operator*			()
{
	return m_resource;
}

// ================================ //
//
template< typename ResourceType >
ResourceType*			ResourcePtr< ResourceType >::operator->			()
{
	return m_resource;
}

// ================================ //
//
template< typename ResourceType >
const ResourceType*		ResourcePtr< ResourceType >::operator*			() const
{
	return m_resource;
}

// ================================ //
//
template< typename ResourceType >
const ResourceType*		ResourcePtr< ResourceType >::operator->			() const
{
	return m_resource;
}

// ================================ //
//
template< typename ResourceType >
inline void				ResourcePtr< ResourceType >::ReleaseResource	()
{
	if( m_resource )
		m_resource->DeleteObjectReference();
	m_resource = nullptr;
}

// ================================ //
//
template< typename ResourceType >
inline void				ResourcePtr< ResourceType >::AssignPointer		( ResourceType* ptr )
{
	if( ptr )
	{
		m_resource = ptr;
		m_resource->AddObjectReference();
	}
}

// ================================ //
//
template< typename ResourceType >
inline ResourceType*	ResourcePtr< ResourceType >::Ptr				() const
{
	return m_resource;
}

}	// sw


//====================================================================================//
//			Register in rttr as wrapper
//====================================================================================//


namespace rttr
{

// This part of code enables ResourcePtr as wrapper for rttr system.


template< typename T >
struct wrapper_mapper< sw::ResourcePtr< T > >
{
    using wrapped_type  = decltype( std::declval< sw::ResourcePtr< T > >().Ptr() );
    using type          = sw::ResourcePtr< T >;

    inline static wrapped_type	get		( const type& obj )
    {
       return obj.Ptr();
    }

    inline static type			create	( const wrapped_type& value )
    {
       return sw::ResourcePtr< T >( value );
    } 
};


} // end namespace rttr
