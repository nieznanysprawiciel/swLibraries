#pragma once
/**@file Deserializer.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Deklaracja klasy deserializatora.*/

#include "Common/TypesDefinitions.h"

#include <string>

struct DeserializerImpl;

/**@brief Tryby parsowania.

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

/**@brief Interfejs deserializator�w.*/
class IDeserializer
{
private:
	DeserializerImpl*		impl;
protected:
public:
	IDeserializer();
	~IDeserializer();

	bool			LoadFromFile	( const std::string& fileName, ParsingMode mode );
	bool			LoadFromString	( const std::string& contentString );


	bool			EnterObject		( const std::string& name );
	bool			EnterArray		( const std::string& name );
	void			Exit			();

	std::string&	GetValue		( const std::string& name, std::string& defaultValue );
	uint32			GetValue		( const std::string& name, uint32 defaultValue );
	uint64			GetValue		( const std::string& name, uint64 defaultValue );
	int32			GetValue		( const std::string& name, int32 defaultValue );
	int64			GetValue		( const std::string& name, int64 defaultValue );
	bool			GetValue		( const std::string& name, bool defaultValue );
	double			GetValue		( const std::string& name, double defaultValue );
};


