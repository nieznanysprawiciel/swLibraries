#pragma once
/**@file Deserializer.h
@author nieznanysprawiciel
@copyright Plik jest czêœci¹ silnika graficznego SWEngine.

@brief Deklaracja klasy deserializatora.*/

#include "Common/TypesDefinitions.h"

#include <string>

struct DeserializerImpl;

/**@brief Interfejs deserializatorów.*/
class IDeserializer
{
private:
	DeserializerImpl*		impl;
protected:
public:
	IDeserializer();
	~IDeserializer();


	std::string&	GetValue		( const std::string& name, std::string& defaultValue );
	uint32			GetValue		( const std::string& name, uint32 defaultValue );
	uint64			GetValue		( const std::string& name, uint64 defaultValue );
	int32			GetValue		( const std::string& name, int32 defaultValue );
	int64			GetValue		( const std::string& name, int64 defaultValue );
	bool			GetValue		( const std::string& name, bool defaultValue );
	double			GetValue		( const std::string& name, double defaultValue );
};


