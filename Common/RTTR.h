#pragma once

// Windows.h header often defines theese macros adn causes conflicts
#undef max
#undef min

#include "swCommonLib/Common//TypesDefinitions.h"

#include "swCommonLib/Reflection/src/rttr/type.h"
#include "swCommonLib/Reflection/src/rttr/rttr_enable.h"
#include "swCommonLib/Reflection/src/rttr/rttr_cast.h"
#include "swCommonLib/Reflection/src/rttr/constructor.h"
#include "swCommonLib/Reflection/src/rttr/destructor.h"
#include "swCommonLib/Reflection/src/rttr/method.h"
#include "swCommonLib/Reflection/src/rttr/property.h"
#include "swCommonLib/Reflection/src/rttr/enumeration.h"
#include "swCommonLib/Reflection/src/rttr/registration.h"
#include "swCommonLib/Reflection/src/rttr/wrapper_mapper.h"



/**@brief Typy metadanych widoczne z poziomu edytora.*/
enum class MetaDataType
{
	Category,			///< Kategoria do jakiej nale�y przypisa� w�a�ciwo�� w edytorze.
	Serialize,			///< Warto�� true oznacza, �e w�a�ciwo�� zostanie zserializowana do pliku z map�. Domy�lnie: true.
	AllowInSaveFile,	///< Serializuje warto�� do pliku z zapisanym stanem gry. Domy�lnie: true.
	ShowInEditor,		///< Umo�liwia odczytywanie i modyfikowanie warto�ci z edytora. Domy�lnie: true. @todo Zaimplementowa� filtrowanie w edytorze properties�w.
	EditorName			///< Nazwa wy�wietlana w edytorze. @todo Zaimplementowa�.
};

typedef rttr::type TypeID;

/**@defgroup Reflection Reflection
@ingroup CommonLibrary
@brief Biblioteka zapewnia dynamiczn� kontrol� typ�w obiekt�w oraz mechanizmy rejestrowania
metainformacji.

Silnik wykorzystuje bibliotek� RTTR autorstwa Axela Menzela udost�pnian� na licencji
MIT z ma�ymi przer�bkami.
Dokumentacja i przyk�ady znajduj� si� na stronie:
http://www.rttr.org/


@section CreatingOwnClasses Tworzenie w�asnych klas


Przy tworzeniu w�asnych klas nale�y dodawa� do nich metainformacje, aby edytor m�g� je poprawnie wy�wietli�.
Wszystkie klasy powinny mie� na samym szczycie hierarchi dziedziczenia obiekt EngineObject.
Je�eli dziedziczy si� po jakiej� silnikowej klasie aktora, to EngineObject w tej hierarchi na pewno si� znajduje.

Pami�ta� o tym nale�y tylko wtedy, gdy tworzy si� jak�� struktur� lub klas�, kt�ra b�dzie polem w klasie aktora.
Aby edytor m�g� wy�wietla� propertisy takiej zagnie�d�onej klasy trzeba jawnie odziedziczy� po EngineObject.

Nale�y mie� na uwadze, �e klasa EngineObject deklaruje metody virtualne biblioteki RTTR, w zwi�zku z czym wszystkie
klasy dziedzicz�ce b�d� mia�y dodatkowe pole ze wska�nikiem na vtable, co zwi�kszy rozmiar takiej struktury. Z tego powodu
lepiej jest, gdy aktorzy nie maj� p�ask� struktur� i takich zagnie�d�onych strutkur si� nie u�ywa, ale nikt nie zabrania.

@todo W obecnej wersji silnika wymaganie posiadania EngineObject w hierarchii nie jest ju� konieczne z punktu widzenia edytora.
W kolejnych wersjach trzeba zmieni� mechanizmy serializacji, �eby potrafi�y zapisywa� r�wnie� takie struktury.

@subsection DeklaringRTTRTypes Deklarowanie typ�w obiekt�w


Biblioteka RTTR wymaga deklarowania nowych typ�w dla kt�re maj� by� przez ni� obs�ugiwane.
Typy proste, kt�re nie maj� by� wy�wietlane w edytorze, ale ma by� dla nich u�ywana statyczna
kontrola typu, mog� zosta� zadeklarowane w nast�puj�cy spos�b:

@code
// Plik .h

struct NewType
{};

//Plik .cpp
RTTR_REGISTRATION
{
    using namespace rttr;
	RTTR_REGISTRATION_STANDARD_TYPE_VARIANTS( NewType )
}
@endcode

Je�eli dla klasy ma by� u�ywana dynamiczna kontrola typ�w, trzeba zadeklarowa�
hierarchi� dziedziczenia w ka�dej z klas. Robi si� to w nast�puj�cy spos�b:

@code
// Plik .h
class StaticActor : public EngineObject
{
	RTTR_ENABLE( EngineObject )
	//...
};
@endcode

Nast�pnie w pliku .cpp mo�na doda� metadane klasy. Nazwy w�asciwo�ci nie powinny zawiera�
bia�ych znak�w, poniewa� to mo�e powodowa� problemy przy serializacji do XMLa.

@code

RTTR_REGISTRATION
{
	rttr::registration::class_< StaticActor >( "StaticActor" )
		.property( "Position", &StaticActor::position )
		(
			rttr::metadata( MetaDataType::Category, "Transformation" ),
			rttr::policy::prop::BindAsPtr()
		)
		.property( "Orientation", &StaticActor::orientation )
		(
			rttr::metadata( MetaDataType::Category, "Transformation" ),
			rttr::policy::prop::BindAsPtr()
		);
}

@endcode

@subsection RTTRNestedClasses Aktorzy z klasami zagnie�d�onymi

Typy z�o�one jak DirectX::XMFLOAT3 powinny by� deklarowane z polityk� rttr::policy::prop::BindAsPtr()
(Tak jak w przyk�adzie powy�ej). W przeciwnym razie edytor nie b�dzie m�g� ich odczytywa� i zapisywa�.
Podobnie sprawa ma si� ze strutkurami wewn�trz klasy np:

@code

struct Nested : public EngineObject
{
	int variable1;
	int variable2;
};

class Actor : public StaticActor
{
public:
	Nested		nestedField;
}

@endcode

W takim przypadku trzeba doda� informacj� o propertisach r�wnie� dla klasy Nested:

@code
// Plik .cpp

RTTR_REGISTRATION
{
	rttr::registration::class_< Nested >( "Nested" )
		.property( "variable1", &Nested::variable1 )
		.property( "variable2", &Nested::variable2 );

	rttr::registration::class_< Actor >( "Actor" )
		.property( "nestedField", &Actor::nestedField )
		(
			rttr::metadata( MetaDataType::Category, "OwnCategory" ),
			rttr::policy::prop::BindAsPtr()
		)
}

#endcode

Typy podstawowe jak
- int
- float
- double
- bool

nie mog� by� deklarowane z polityk� BindAsPtr.

@subsection PrivateMembers Prywatne sk�adowe klasy

W przypadku prywatnych sk�adowych, deklaracja metadanych nie skompiluje si�, poniewa� prywatne pola s� niedost�pne
na zewn�trz klasy. Aby m�c je zadeklarowa� nale�y doda� makro RTTR_REGISTRATION_FRIEND.

@code

class StaticActor : public EngineObject
{
	RTTR_ENABLE( EngineObject )
	RTTR_REGISTRATION_FRIEND
	//...
};
@endcode

*/

#define BIND_AS_PTR		( rttr::policy::prop::bind_as_ptr )
#define BIND_AS_REF		( rttr::policy::prop::as_reference_wrapper )


