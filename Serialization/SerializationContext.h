#pragma once
/**@file SerializationContext
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Interface kontekstu serializacji i deserializacji.*/




/**@brief Interface kontekstu serializacji i deserializacji.
@ingroup Serialization

W klasach pochodnych nale�y umie�ci� dowolne dane, kt�re s� potrzebne w trakcie serializacji.*/
struct SerializationContext
{
public:

				SerializationContext() = default;	///
	virtual		~SerializationContext() = default;	///

};


