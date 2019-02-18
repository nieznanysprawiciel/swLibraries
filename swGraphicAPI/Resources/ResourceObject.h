#pragma once
/**
@file Resource.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Serialization/PropertySerialization/EngineObject.h"
//#include <atomic>


class Resource;

typedef uint32 ResourceID;

namespace sw
{
	template< class ResourceType > class ResourceContainer;
}


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
*/
class Resource : public sw::EngineObject
{
	RTTR_ENABLE( sw::EngineObject );
	RTTR_REGISTRATION_FRIEND
private:
	unsigned int			m_objectReferences;	///< Liczba assetów, które sie odwo³uj¹. @todo To powinien byæ std::atomic_uint, ale wtedy nie kompiluje siê z CLRem.
	ResourceID				m_uniqueId;			///< Unikalny identyfikator zasobu.

protected:
	virtual ~Resource() = default;		///<Nie ka¿dy mo¿e skasowaæ obiekt

public:
	/**Ustawia zerow¹ liczbê odwo³añ.*/
	Resource( ResourceID id )
	{
		m_objectReferences = 0;
		m_uniqueId = id;
	}

	/**@todo Add ResourceAccessKey*/
	inline void			SetID( ResourceID id ) { m_uniqueId = id; }	///<Ustawia identyfikator obiektu

	///sprawdza czy mo¿na zwolniæ zmienn¹
	inline bool			CanDelete( unsigned int& objectRef );
	inline bool			CanDelete();

	inline void			Delete	( ResourceAccessKey< Resource > ) { delete this; }

	/**Funkcje s³u¿¹ce do zarz¹dzania odwo³aniami.
	Nale¿y pilnowaæ, aby wszystkie funkcje, które modyfikuj¹ jakiekolwiek przypisania obiektów
	do tekstur, materia³ów i meshy, modyfikowa³y równie¿ iloœæ odwo³añ.
	U¿ytkownik silnika powinien mieæ udostêpnion¹ wartstwê poœredniczac¹, ¿eby nie musia³
	pamiêtaæ o odwo³aniach.*/
	inline void			AddAssetReference()		{ ++m_objectReferences; }	///< Dodaje odwo³anie plikowe do assetu
	inline void			AddObjectReference()	{ ++m_objectReferences; }	///< Dodaje odwo³anie bezpoœrednie obiektu do assetu
	inline void			DeleteAssetReference()	{ --m_objectReferences; }	///< Kasuje odwo³anie plikowe do assetu
	inline void			DeleteObjectReference()	{ --m_objectReferences; }	///< Kasuje odwo³anie bezpoœrednie obiektu do assetu

	inline ResourceID	GetID()			{ return m_uniqueId; }		///< Zwraca identyfikator nadany assetowi

	virtual std::string GetResourceName() const = 0;				///< Zwraca nazwê zasobu. To mo¿e byæ nazwa pliku, na podstawie którego stworzono zasób, ale zasadniczo interpretacja jest dowolna.

public:

	virtual bool		IsCacheable		() { return false;  }
};




//----------------------------------------------------------------------------------------------//
//									Resource											//
//----------------------------------------------------------------------------------------------//

//==============================================================================================//



/**@brief Funkcja informuje czy obiekt s¹ obiektu, które odwo³uj¹ siê do assetu.

@param[out] file_ref W zmiennej zostanie umieszczona liczba referencji plikowych.
@param[out] other_ref W zmiennej zostanie umieszczona liczba referencji bezpoœrednich od obiektów.
@return Zwraca wartoœæ logiczn¹ mówi¹c¹ czy asset nadaje siê do usuniêcia.
*/
inline bool Resource::CanDelete( unsigned int& objectRef )
{
	objectRef = m_objectReferences;

	if( m_objectReferences == 0 )
		return true;
	return false;
}

/**@brief Funkcja informuje czy obiekt s¹ obiektu, które odwo³uj¹ siê do assetu.

@return Zwraca wartoœæ logiczn¹ mówi¹c¹ czy asset nadaje siê do usuniêcia.
*/
inline bool Resource::CanDelete()
{
	if( m_objectReferences == 0 )
		return true;
	return false;
}
