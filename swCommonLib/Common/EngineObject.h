#pragma once
/**@file ActorBase.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief */

#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/TypesDefinitions.h"

class ISerializer;
class IDeserializer;


/**@brief Klasa bazowa dla obiekt�w, kt�re maj� by� dost�pne w edytorze
poprzez rttr. Nale�y po niej odziedziczy� i doda� odpowiednie deklaracje.

@todo Dobrze by by�o, gdyby EngineObject implementowa� domy�ln� serializacj�, ale wtedy jest problem,
�e nie wiadomo, kt�ra z bibliotek powinna t� implementacj� kompilowa�.

@ingroup Reflection*/
class EngineObject
{
	RTTR_ENABLE()

public:
	inline TypeID		GetType			() const		{ return this->get_type(); }
	inline std::string	GetTypeName		() const		{ return std::string( this->get_type().get_name() ); }


	/**@brief Implements default serialization.
	@detail Serializes only declared properties.*/
	virtual void		Serialize		( ISerializer* ser ) const;

	/**@brief Implements default deserialization.*/
	virtual void		Deserialize		( IDeserializer* deser );

	/// Zwraca ilo�� pami�ci zajmowanej przez obiekt. Implementacje w klasach potomnych powinny te�
	/// dolicza� rekurencyjnie pami�� zajmowan� przez obiekty, kt�rych w�a�cicielem jest ten obiekt.
	virtual Size		MemorySize		()							{ return this->get_type().get_sizeof(); }

	template< typename TargetType >
	TargetType*			DynamicCast		()							{ return rttr::rttr_cast< TargetType* >( this ); }
};

