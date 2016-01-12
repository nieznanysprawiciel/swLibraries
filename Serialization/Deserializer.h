#pragma once
/**@file Deserializer.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.

@brief Deklaracja klasy deserializatora.*/

#include "Common/TypesDefinitions.h"

#include <string>

struct DeserializerImpl;

/**@brief Tryby parsowania.

Parsowanie insitu powoduje zapisanie ca³ego parsowanego dokumentu w pamiêci deserializatora.
Nowe stringi nie s¹ alokowane, a zapisywane s¹ wska¿niki do tego dokumentu.
Metoda prawdopodobnie zajmie wiêcej pamiêci ni¿ w przypadku alokowania, poniewa¿
przechowywane s¹ równie¿ nadmiarowe bia³e znaki i wszystkie niepotrzebne elementy.
Zalet¹ jest za to unikanie alokacji, co powinno przypsieszyæ dzia³anie.

AllocString usuwa ca³y dokument z pamiêci po sparsowaniu.
Metoda dzia³a wolniej, ale za to przechowuje tylko to co potrzebne.
Wskazaniem do u¿ycia s¹ przypadki, gdy deserializator s³u¿y nie tylko
do jednokrotnego parsowania, ale równie¿ przechowywania danych.*/
enum class ParsingMode
{
	ParseInsitu,		///< Nie alokuje stringów, ale zapisuje sobie wskaŸniki na miejsca w parsowanym tekœcie.
	AllocStrings		///< Przy parsowaniu alokuje nowe stringi.
};

/**@brief Interfejs deserializatorów.*/
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


