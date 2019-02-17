#pragma once
/**
@file ResourceContainer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/System/Path.h"



#include <map>
#include <vector>
#include <type_traits>

#include "swGraphicAPI/Resources/ResourcePtr.h"


namespace sw
{




/**@brief Container for resources.

Resources are identified by their path.*/
template< class ResourceType >
class ResourceContainer
{
	friend class AssetsManager;
	friend class ResourceManager;
	friend class nResourceManager;
private:
	ResourceID		m_counter;		///< Identifier for next resource.

protected:
	std::map< filesystem::Path, ResourceType* >		m_resMap;	///< Maps assets names/paths to Resources.


protected:

	// Deleting objects.
	bool			ForceRemove			( const filesystem::Path& name );
	bool			ForceRemove			( ResourceID id );
	void			ForceRemoveAll		();
	void			ReleaseMemory		( ResourceType* );

public:
	ResourceContainer();
	~ResourceContainer();

	// Deleting objects.
	bool			Remove				( const filesystem::Path& name );
	bool			Remove				( ResourceID id );
	uint32			RemoveUnused		();

	// Adding objects
	void			UnsafeAdd			( const filesystem::Path& name, ResourceType* resource );

	// Resources access.
	ResourceType*	Get					( ResourceID id );

	/**@brief Zwraca element na podstawie jego nazwy
	@param[in] name Nazwa elementu, który chcemy dostaæ
	@return WskaŸnik na obiekt assetu*/
	inline ResourceType*		Get		( const filesystem::Path& name )
	{
		auto iter = m_resMap.find( name );
		if( iter != m_resMap.end() )
			return iter->second;
		return nullptr;
	}

	/**@brief Finds resource matching given descriptor.

	Resource must implement GetDescriptor function.
	Descriptor must implement operator==.

	Function finds resource in linear time. Use only for small containers.*/
	template< typename DescType >
	ResourceType*				Find		( const DescType& desc );

	// Listing resources.
	template< typename ResourceCastType >
	std::vector< ResourcePtr< ResourceCastType > >		List();

	inline uint32				GetNextId() { return count; }	///< Returns idetifier for next resource of this type.
};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< class ResourceType >
ResourceContainer< ResourceType >::ResourceContainer()
{
	count = 1;
}

/**@brief Releases all assets.*/
template< class ResourceType >
ResourceContainer< ResourceType >::~ResourceContainer()
{
	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); iter++ )
	{
		ReleaseMemory( iter->second );
	}
	m_resMap.clear();
}

/**@brief Returns resource base on identifier.

Searching in linear time.

@param[in] id Resource identifier.
@return Resource pointer*/
template< class ResourceType >
ResourceType*			ResourceContainer< ResourceType >::Get				( ResourceID id )
{
	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); iter++ )
	{
		if( iter->second->GetID() == id )
			return iter->second;
	}
	return nullptr;
}

// ================================ //
//
template< class ResourceType >
template< typename DescType >
inline ResourceType*	ResourceContainer< ResourceType >::Find				( const DescType& desc )
{
	static_assert( std::is_member_function_pointer< decltype( &ResourceType::GetDescriptor ) >::value, "ResourceType must implement GetDescriptor function." );

	for( auto& resource : m_resMap )
	{
		if( resource.second->GetDescriptor() == desc )
			return resource.second;
	}
	return nullptr;
}


//-------------------------------------------------------------------------------//
//							Adding elements
//-------------------------------------------------------------------------------//



/**@brief Adds resource without checking it's existance.
Resource will be overwritten if it existed.*/
template< class ResourceType >
void					ResourceContainer< ResourceType >::UnsafeAdd		( const filesystem::Path& name, ResourceType* resource )
{
	if( !resource )
		return;

	m_resMap[ name ] = resource
	resource->SetID( m_counter++ );
}

//-------------------------------------------------------------------------------//
//							Removing resources
//-------------------------------------------------------------------------------//


/**@brief Release resource.*/
template< class ResourceType >
void					ResourceContainer< ResourceType >::ReleaseMemory		( ResourceType* object )
{
	object->Delete( ResourceAccessKey< ResourceType >() );
}

/**@brief Removes resource if it's posible.
@return Returns false if resource doesn't exist or it still has references.*/
template< class ResourceType >
bool					ResourceContainer< ResourceType >::Remove				( const filesystem::Path& name )
{
	auto iter = m_resMap.find( name );
	if( iter != m_resMap.end() )
		return false;

	if( !iter->second->CanDelete() )
		return false;

	ReleaseMemory( iter->second );
	m_resMap.erase( iter );

	return true;
}


/**@brief Removes resource if it's posible.
@return Returns false if resource doesn't exist or it still has references.*/
template <class ResourceType>
bool					ResourceContainer< ResourceType >::Remove				( ResourceID id )
{
	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); iter++ )
	{
		if( iter->second->GetID() == id )
		{
			if( !iter->second->CanDelete() )
				return false;

			ReleaseMemory( iter->second );
			m_resMap.erase( iter );

			return true;
		}
	}
	return false;
}

/**@brief Removes all resources witout references.
@return Returns number of deleted elements.*/
template< class ResourceType >
uint32					ResourceContainer< ResourceType >::RemoveUnused			()
{
	int count = 0;
	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); iter++ )
	{
		if( iter->second->CanDelete() )
		{
			ReleaseMemory( iter->second );
			m_resMap.erase( iter );

			++count;
		}
	}

	return count;
}


/**@brief Removes resource even if it's reference count is greater then 0.
@return Returns false if resource doesn't exist.*/
template< class ResourceType >
bool					ResourceContainer< ResourceType >::ForceRemove			( const filesystem::Path& name )
{
	auto iter = m_resMap.find( name );
	if( iter != m_resMap.end() )
		return false;

	delete iter->second;
	return true;
}

/**@brief Removes resource even if it's reference count is greater then 0.
@return Returns false if resource doesn't exist.*/
template< class ResourceType >
bool					ResourceContainer< ResourceType >::ForceRemove			( ResourceID id )
{
	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); iter++ )
	{
		if( iter->second->GetID() == id )
		{
			delete iter->second;
			return true;
		}
	}
	return false;
}

/**@brief removes all elements.*/
template< class ResourceType >
void					ResourceContainer< ResourceType >::ForceRemoveAll		()
{
	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); iter++ )
	{
		delete iter->second;
	}
	m_resMap.clear();
}

/**@brief Lists all elements in ResourceContainer.*/
template< class ResourceType >
template< typename ResourceCastType >
inline std::vector< ResourcePtr< ResourceCastType > >		ResourceContainer< ResourceType >::List()
{
	std::vector< ResourcePtr< ResourceCastType > > resourcesList;
	resourcesList.reserve( m_resMap.size() );

	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); iter++ )
	{
		resourcesList.push_back( ResourcePtr< ResourceCastType >( iter->second ) );
	}

	return resourcesList;
}
}	// sw

