#pragma once

/**@file ResourceContainer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.


@brief Zawiera deklaracj� szblonu klasy kontenera dla asset�w.
*/

///@todo Doda� IDki obok �cie�ek.
///@todo Kontrner powinien obs�ugiwa� �cie�ki, jako obiekty typu Path zamiast wstring�w.
//#include "swCommonLib/Common/System/Path.h"

#include <map>
#include <vector>
#include <type_traits>

#include "swGraphicAPI/Resources/ResourcePtr.h"


/**
@brief Szablon klasy do przechowywania asset�w.

Wszystkie assety s� identyfikowane po nazwie, kt�ra najcz�ciej jest nazw� pliku, z kt�rego asset
pochodzi. Mapa zapewnia logarytmiczny czas dost�pu po nazwie. Istnieje te� mo�liwo�� odwo�ania si�
po identyfikatorze, wtedy czas dost�pu jest liniowy (chyba �e iterowanie po kolejnych elementacj mapy
nie odbywa si� liniowo.*/
template < class TYPE >
class ResourceContainer
{
	friend class AssetsManager;
	friend class ResourceManager;
private:
	unsigned int count;		///<Indentyfikator jaki zostanie przydzielony kolejnemy elementowi

protected:
	std::map<std::wstring, TYPE*> container;	///<Kontener zawieraj�cy assety powiazane z ich nazw�

	// Kasowanie obiekt�w
	int		ForceRemove			( const std::wstring& name );
	int		ForceRemove			( unsigned int id );
	void	ForceRemoveAll		();
	void	ReleaseMemory		( TYPE* );
public:
	ResourceContainer();
	~ResourceContainer();

	// Kasowanie obiekt�w
	int		Remove				( const std::wstring& name );
	int		Remove				( unsigned int id );
	int		RemoveUnused		();

	// Dodawanie obiekt�w
	void	UnsafeAdd			( const std::wstring& name, TYPE* resource );

	// Dost�p do obiekt�w
	TYPE*	get					( unsigned int id );
	inline unsigned int			GetNextId() { return count; }	///<Zwraca identyfikator, kt�ry zostanie przydzielony kolejnemu elementowi

	/**@brief Zwraca element na podstawie jego nazwy
	@param[in] name Nazwa elementu, kt�ry chcemy dosta�
	@return Wska�nik na obiekt assetu*/
	inline TYPE* get( const std::wstring& name )
	{
		auto iter = container.find( name );
		if ( iter != container.end() )
			return iter->second;
		return nullptr;
	}

	/**@brief Finds resource matching given descriptor.
	
	Resource must implement GetDescriptor function.
	Descriptor must implement operator==.
	
	Function finds resource in linear time. Use only for small containers.*/
	template< typename DescType >
	TYPE*	Find				( const DescType& desc );

	// Listowanie obiekt�w.
	std::vector< ResourcePtr< TYPE > >		List();
};

template <class TYPE>
ResourceContainer<TYPE>::ResourceContainer()
{
	count = 1;
}

/**@brief Destruktor zwalnia wszystkie elementy w mapie (tak�e pami�� po nich)*/
template <class TYPE>
ResourceContainer<TYPE>::~ResourceContainer( )
{
	for ( auto iter = container.begin( ); iter != container.end( ); iter++ )
	{
		ReleaseMemory( iter->second );
	}
	container.clear();
}

/**@brief Zwraca element na podstawie identyfikatora.

Wyszukiwanie po identyfikatorze jest liniowe, a po nazwie logarytmiczne.
Jednak�e por�wnania string�w mog� si� okaza� bardziej kosztowne.
@param[in] id Identyfikator elementu.
@return Wska�nik na poszukiwany element.*/
template <class TYPE>
TYPE*			ResourceContainer<TYPE>::get	( unsigned int id )
{
	for ( auto iter = container.begin(); iter != container.end(); iter++ )
	{
		if ( iter->second->GetID() == id )
			return iter->second;
	}
	return nullptr;
}

// ================================ //
//
template< class TYPE >
template< typename DescType >
inline TYPE*	ResourceContainer< TYPE >::Find	( const DescType& desc )
{
	static_assert( std::is_member_function_pointer< decltype( &TYPE::GetDescriptor ) >::value, "TYPE must implement GetDescriptor function." );

	for( auto& resource : container )
	{
		if( resource.second->GetDescriptor() == desc )
			return resource.second;
	}
	return nullptr;
}


//-------------------------------------------------------------------------------//
//							dodawanie obiekt�w
//-------------------------------------------------------------------------------//

/*Dodaje element do kontanera + nadaje mu unikalny identyfikator.
Je�eli element ju� istnia�, to po prostu nie zostanie wstawiony, dlatego
przed uzyciem warto pobra� element o danej nazwie, �eby sprawdzi�
czy dodawanie jest konieczne.*/
// Mo�e kiedy� zrobie wstawianie ze sprawdzaniem, na razie nie wydaje si� potrzebne


/**@brief Dodaje element do kontanera + nadaje mu unikalny identyfikator.

Je�eli element ju� istnia�, to zostanie nadpisany nowym, dlatego nale�y
zawsze przed u�yciem sprawdzi� czy pod tak� nazw�, co� ju� si� nie 
znajduje.
@param[in] name Nazwa elementu, pod jak� zostanie dodany.
@param[in] resource Element dodania.*/
template <class TYPE>
void ResourceContainer<TYPE>::UnsafeAdd( const std::wstring& name, TYPE* resource )
{
	if ( !resource )
		return;	//Nie mo�emy potem ustawi� id

	container[name] = resource;

	resource->SetID( count );
	++count;			// Inkrementujemy licznik
}

//-------------------------------------------------------------------------------//
//							kasowanie obiekt�w
//-------------------------------------------------------------------------------//
/**@brief Zwalnia obiekt podany w parametrze.

Kasowanie pami�ci nie jest mo�liwe przy pomocy operatora delete,
poniewa� destruktory w tych klasach s� prywatne. Dlatego trzeba zrobi� to 
za po�rednictwem obiektu, kt�ry ma uprawnienia do tego.

@param[in] object Objekt do skasowania.
*/
template <class TYPE>
void ResourceContainer<TYPE>::ReleaseMemory( TYPE* object )
{
	// Destruktor jest prywatny, wi�c nie mo�emy kasowa� obiektu bezpo�rednio.
	ObjectDeleterKey<TYPE> key;							// Tworzymy klucz.
	ObjectDeleter<TYPE> model_deleter( key );			// Tworzymy obiekt kasuj�cy i podajemy mu nasz klucz.
	model_deleter.delete_object( object );				// Kasujemy obiekt za po�rednictwem klucza.
}

/**@brief Usuwa element o podanej nazwie, je�eli nie ma do niego odwo�a�.

@param[in] name nazwa elementu do usuni�cia.
@return Zwracana warto��:
- 0	-	w przypadku powodzenia,
- -1	-	nie znaleziono elementu,
- 1	-	nie da si� usun��, bo jest w u�yciu*/
template <class TYPE>
int ResourceContainer<TYPE>::Remove( const std::wstring& name )
{
	auto iter = container.find( name );
	if ( iter != container.end() )
		return -1;		// Nie znale�li�my elementu

	if ( !iter->second->CanDelete() )
		return 1;		// Nie mo�emy skasowa�, bo s� odwo�ania

	ReleaseMemory( iter->second );		// Zwalniamy pami�� spod wska�nika
	container.erase( iter );	// Kasujemy element z mapy

	return 0;			// Wychodzimy z powodzeniem
}


/**@brief Usuwa element o podanym indeksie, je�eli nie ma do niego odwo�a�.

@param[in] id Identyfikator elementu
@return Zwracana warto��:
- 0	-	w przypadku powodzenia,
- -1	-	nie znaleziono elementu,
- 1	-	nie da si� usun��, bo jest w u�yciu*/
template <class TYPE>
int ResourceContainer<TYPE>::Remove( unsigned int id )
{
	for ( auto iter = container.begin( ); iter != container.end( ); iter++ )
	{
		if ( iter->second->GetID() == id )
		{
			// Sprawdzamy czy nie ma jakich� odwo�a� do obiektu
			if ( !iter->second->CanDelete() )
				return 1;				// S� odwo�ania, wi�c nie kasujemy

			ReleaseMemory( iter->second );		// Zwalniamy pami�� spod wska�nika
			container.erase( iter );	// Kasujemy element z mapy

			return 0;					// Zwracamy 0 jako powodzenie operacji
		}
	}
	return -1;		// Nie znale�li�my elementu
}

/**@brief Kasuje wszystkie elementy w kontenerze, kt�re nie s� u�ywane przez
�aden obiekt. Kasowanie jest w pe�ni bezpieczne.

@return Zwraca liczb� usuni�tych element�w.*/
template <class TYPE>
int ResourceContainer<TYPE>::RemoveUnused()
{
	int count = 0;
	for ( auto iter = container.begin(); iter != container.end(); iter++ )
	{// Iterujemy po ca�ej mapie
		if ( iter->second->CanDelete() )
		{
			// Mo�emy skasowa� obiekt, bo nikt go nie u�ywa
			ReleaseMemory( iter->second );		// Zwalniamy pami�� spod wska�nika
			container.erase( iter );	// Kasujemy element z mapy

			++count;
		}
	}

	return count;
}


/**@brief Wymusza skasowanie podanego elementu, nawet je�eli jest u�ywany

@param[in] name Nazwa elementu do usuni�cia.
@return Zwracana warto��:
- 0	-	w przypadku powodzenia,
- -1	-	nie znaleziono elementu*/
template <class TYPE>
int ResourceContainer<TYPE>::ForceRemove( const std::wstring& name )
{
	auto iter = container.find( name );
	if ( iter != container.end( ) )
		return -1;		// Nie znale�li�my elementu

	delete iter->second;		// Zwalniamy pami�� spod wska�nika
	return 0;
}

/**@brief Wymusza skasowanie podanego elementu

@param[in] id Identyfkator elementu do usuni�cia
@return Zwracana warto��:
- 0	-	w przypadku powodzenia,
- -1	-	nie znaleziono elementu*/
template <class TYPE>
int ResourceContainer<TYPE>::ForceRemove( unsigned int id )
{
	for ( auto iter = container.begin( ); iter != container.end( ); iter++ )
	{
		if ( iter->second->GetID( ) == id )
		{
			delete iter->second;		// Zwalniamy pami�� spod wska�nika
			return 0;
		}
	}
	return -1;		// Nie znaleziono elementu
}

/**@brief Kasuje wszystkie elementy niezale�nie od tego czy by�y u�ywane,
a nast�pnie czy�ci map�.*/
template <class TYPE>
void ResourceContainer<TYPE>::ForceRemoveAll( )
{
	for ( auto iter = container.begin(); iter != container.end(); iter++ )
	{// Iterujemy po ca�ej mapie
		delete iter->second;		// Zwalniamy pami�� spod wska�nika
	}
	container.clear();
}

/**@brief Listuje wszystkie assety danego typu.*/
template< class TYPE >
inline std::vector< ResourcePtr< TYPE > > ResourceContainer< TYPE >::List()
{
	std::vector< ResourcePtr< TYPE > > resourcesList;
	resourcesList.reserve( container.size() );

	for( auto iter = container.begin(); iter != container.end(); iter++ )
	{
		resourcesList.push_back( ResourcePtr< TYPE >( iter->second ) );
	}

	return resourcesList;
}

