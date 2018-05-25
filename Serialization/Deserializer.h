#pragma once
/**@file Deserializer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Deklaracja klasy deserializatora.*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swCommonLib/Serialization/ISerializationContext.h"

#include <string>
#include <memory>

struct DeserializerImpl;

/**@brief Parsing modes.
@ingruop Serialization

Parsowanie insitu powoduje zapisanie ca�ego parsowanego dokumentu w pami�ci deserializatora.
Nowe stringi nie s� alokowane, a zapisywane s� wska�niki do tego dokumentu.
Metoda prawdopodobnie zajmie wi�cej pami�ci ni� w przypadku alokowania, poniewa�
przechowywane s� r�wnie� nadmiarowe bia�e znaki i wszystkie niepotrzebne elementy.
Zalet� jest za to unikanie alokacji, co powinno przypsieszy� dzia�anie.

AllocString usuwa ca�y dokument z pami�ci po sparsowaniu.
Metoda dzia�a wolniej, ale za to przechowuje tylko to co potrzebne.
Wskazaniem do u�ycia s� przypadki, gdy deserializator s�u�y nie tylko
do jednokrotnego parsowania, ale r�wnie� przechowywania danych.*/
enum class ParsingMode
{
	ParseInsitu,		///< Nie alokuje string�w, ale zapisuje sobie wska�niki na miejsca w parsowanym tek�cie.
	AllocStrings		///< Przy parsowaniu alokuje nowe stringi.
};

/**@brief Interface for deserializers.

@ingroup Serialization*/
class IDeserializer
{
private:
	DeserializerImpl*							impl;
	ISerializationContextPtr					context;
protected:
public:
	IDeserializer		();
	IDeserializer		( ISerializationContextPtr serContext );
	~IDeserializer		();

	bool			LoadFromFile	( const std::string& fileName, ParsingMode mode );
	bool			LoadFromString	( const std::string& contentString );

	const char*		GetName			() const;

	bool			EnterObject		( const std::string& name ) const;
	bool			EnterArray		( const std::string& name ) const;
	bool			EnterObject		( const char* name ) const;
	bool			EnterArray		( const char* name ) const;
	void			Exit			() const;

	bool			FirstElement	() const;
	bool			NextElement		() const;
	bool			PrevElement		() const;
	bool			LastElement		() const;

	std::string		GetAttribute		( const std::string& name, std::string& defaultValue ) const;
	const char*		GetAttribute		( const std::string& name, const char* defaultValue ) const;
	uint32			GetAttribute		( const std::string& name, uint32 defaultValue ) const;
	uint64			GetAttribute		( const std::string& name, uint64 defaultValue ) const;
	int32			GetAttribute		( const std::string& name, int32 defaultValue ) const;
	int64			GetAttribute		( const std::string& name, int64 defaultValue ) const;
	bool			GetAttribute		( const std::string& name, bool defaultValue ) const;
	double			GetAttribute		( const std::string& name, double defaultValue ) const;

	std::string		GetAttribute		( const char* name, std::string& defaultValue ) const;
	const char*		GetAttribute		( const char* name, const char* defaultValue ) const;
	uint32			GetAttribute		( const char* name, uint32 defaultValue ) const;
	uint64			GetAttribute		( const char* name, uint64 defaultValue ) const;
	int32			GetAttribute		( const char* name, int32 defaultValue ) const;
	int64			GetAttribute		( const char* name, int64 defaultValue ) const;
	bool			GetAttribute		( const char* name, bool defaultValue ) const;
	double			GetAttribute		( const char* name, double defaultValue ) const;


	std::string		GetError			() const;

public:

	/**@brief Zwraca kontekst serializacji.
	
	Funkcja sprawdza typ kontekstu jedynie w trybie debug (assert).*/
	template< typename ContextType >
	inline ContextType*			GetContext	() const
	{
		assert( context != nullptr );
		
		// Sprawdzanie dynamicznego typu tylko, je�eli w��czone jest RTTI.
#ifdef _CPPRTTI
		assert( typeid( *context ) == typeid( ContextType ) );
#endif

		return static_cast< ContextType* >( context.get() );
	}

};


