#pragma once
/**
@file ResourceContainer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/System/Path.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"


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
	std::map< AssetPath, ResourceType* >		m_resMap;	///< Maps assets names/paths to Resources.


protected:

	// Deleting objects.
	bool			ForceRemove			( const AssetPath& name );
	bool			ForceRemove			( ResourceID id );
	void			ForceRemoveAll		();
	void			ReleaseMemory		( ResourceType* );

public:
	ResourceContainer();
	~ResourceContainer();

	// Deleting objects.
	bool			Remove				( const AssetPath& name );
	bool			Remove				( ResourceID id );
	Size			RemoveUnused		();

	// Adding objects
	void			UnsafeAdd			( const AssetPath& name, ResourceType* resource );
	bool			SafeAdd				( const AssetPath& name, ResourceType* resource );

	// Resources access.
	ResourceType*	Get					( ResourceID id );

	/**@brief Zwraca element na podstawie jego nazwy
	@param[in] name Nazwa elementu, kt�ry chcemy dosta�
	@return Wska�nik na obiekt assetu*/
	inline ResourceType*		Get		( const AssetPath& name )
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
	std::vector< ResourcePtr< ResourceCastType > >		List() const;

	inline uint32				GetNextId() { return count; }	///< Returns idetifier for next resource of this type.
};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
template< class ResourceType >
ResourceContainer< ResourceType >::ResourceContainer()
	:	m_counter( 1 )
{}

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
void					ResourceContainer< ResourceType >::UnsafeAdd		( const AssetPath& name, ResourceType* resource )
{
	if( !resource )
		return;

	m_resMap[ name ] = resource;
	resource->SetID( m_counter++ );
}

/**@brief Adds resource only if it didn't existed.*/
template< class ResourceType >
inline bool				ResourceContainer< ResourceType >::SafeAdd			( const AssetPath& name, ResourceType* resource )
{
	if( !resource )
		return false;

	auto insertResult = m_resMap.insert( std::make_pair( name, resource ) );
	
	// Check if element existed.
	if( insertResult.second == false )
		return false;

	return true;
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
bool					ResourceContainer< ResourceType >::Remove				( const AssetPath& name )
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
Size					ResourceContainer< ResourceType >::RemoveUnused			()
{
	int count = 0;
	for( auto iter = m_resMap.begin(); iter != m_resMap.end(); )
	{
		if( iter->second->CanDelete() )
		{
			ReleaseMemory( iter->second );
			iter = m_resMap.erase( iter );

			++count;
		}
		else
		{
			iter++;
		}
	}

	return count;
}


/**@brief Removes resource even if it's reference count is greater then 0.
@return Returns false if resource doesn't exist.*/
template< class ResourceType >
bool					ResourceContainer< ResourceType >::ForceRemove			( const AssetPath& name )
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
inline std::vector< ResourcePtr< ResourceCastType > >		ResourceContainer< ResourceType >::List	() const
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

