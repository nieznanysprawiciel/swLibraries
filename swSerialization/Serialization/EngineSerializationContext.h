#pragma once
/**
@file EngineSerializationContext.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swSerialization/Interfaces/ISerializationContext.h"

#include <map>
#include <vector>



struct EngineSerializationContext : public ISerializationContext
{
	typedef std::map< rttr::type, std::vector< rttr::property > > TypePropertyMap;
public:

	bool					SaveWholeMap;		///< Warto�� true oznacza, �e zapisujemy map�, false, �e zapisujemy stan gry.
	bool					EditorLoad;			///< Wczytywanie mapy w trybie edytora.

	TypePropertyMap			TypeProperties;		///< Mapa zawieraj�ca typy i ich w�a�ciwo�ci. W�a�ciwo�ci nieserializowane s� odfiltrowane.



public:
	virtual		~EngineSerializationContext() = default;
};

