#pragma once
/**
@file Resource.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/AssetPath.h"
//#include <atomic>

#include <string>


namespace sw
{


class Resource;

typedef uint32 ResourceID;
template< class ResourceType > class ResourceContainer;



/**@brief Class Restricts access to some functions only for chosen classes.*/
template< typename ResType >
class ResourceAccessKey
{
	friend class nResourceManager;
	friend class sw::ResourceContainer< ResType >;

private:
	ResourceAccessKey() = default;							///< Only friend class can create key.
	ResourceAccessKey( const ResourceAccessKey& ) {}		///< Only friend class can create key.
	ResourceAccessKey( const ResourceAccessKey&& ) {}		///< Only friend class can create key.
public:
};



/**@brief Base class for all assets and resources. It supports reference counting.
@ingroup GraphicAPI

Resource can be referenced from multiple actors or other assets. All references should remember to increment and decrement
reference counter to avoid deletion. Use class ResourcePtr for this purpose.

@todo Zliczanie referencji w Resource nie nadaje siê do wielow¹tkowoœci. Poprawiæ w odpowiednim momencie.
@todo Rename ResourceObject.h to Resoruce.h
*/
class Resource : public EngineObject
{
	RTTR_ENABLE( EngineObject );
	RTTR_REGISTRATION_FRIEND
private:

	uint32			m_references;			///< Number of references to this Resource. (@todo This should be atomic, but atomics won't compile with CLR).
	std::string		m_name;			

protected:

	virtual				~Resource		() = default;

public:
	
	explicit			Resource		( const AssetPath& assetPath )
		:	m_references( 0 )
		,	m_name( assetPath.String() )
	{}


	/**@brief Checks if Resource can be deleted - that means how many references objects has.
	param[out] objectRef Will be set to number of references.*/
	inline bool			CanDelete		( uint32& objectRef ) const;
	inline bool			CanDelete		() const;

	inline void			Delete			( ResourceAccessKey< Resource > ) { delete this; }

	/**@brief Reference counting functions.
	Use ResourcePtr to manage reference count.*/
	inline void			AddAssetReference		() { ++m_references; }
	inline void			AddObjectReference		() { ++m_references; }
	inline void			DeleteAssetReference	() { --m_references; }
	inline void			DeleteObjectReference	() { --m_references; }

	/**@brief Returns name of resource.
	Default implementation returns AssetPath converted to string.*/
	virtual std::string			GetResourceName			() const;

	/**@brief Returns AssetPath object.*/
	virtual AssetPath			GetAssetPath			() const;

	/**@brief Returns Resource path in filesystem*/
	virtual filesystem::Path	GetFilePath				() const;

public:

	/**@brief Override in derived classes, if objects is suitable to be cached.*/
	virtual bool		IsCacheable				() const { return false; }

protected:

	void				SetAssetPath			( const AssetPath& assetPath )		{ m_name = assetPath.String(); }
};

typedef ResourcePtr< Resource > ResourcePointer;


//----------------------------------------------------------------------------------------------//
//									Resource													//
//----------------------------------------------------------------------------------------------//

//==============================================================================================//


// ================================ //
//
inline bool						Resource::CanDelete			( uint32& objectRef ) const
{
	objectRef = m_references;

	if( m_references == 0 )
		return true;
	return false;
}

// ================================ //
//
inline bool						Resource::CanDelete			() const
{
	if( m_references == 0 )
		return true;
	return false;
}


}	// sw

