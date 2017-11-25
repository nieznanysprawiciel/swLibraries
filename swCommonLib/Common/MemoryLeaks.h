/**@file memory_leaks.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Plik s�u�y do wykrywania wyciek�w pami�ci.
*/

/**@brief Plik umo�liwiaj�cy �ledzenie wyciek�w pami�ci.

Aby uruchomi� sprawdzanie wyciek�w pami�ci nale�y zaincludowa� ten plik w testowanym pliku .cpp.
Aby wszystko kompilowa�o si� poprawnie, musi by� on ostatnim do��czanym plikiem ze wszystkich.
W innym razie definicje b�d� oddzia�ywa�y tak�e na wszystki zaincludowane pliki poni�ej tego, co powoduje
nieprzewidywalne dzia�anie.

Informacje o wyciekach s� wypisywane na standardowe wyj�cie, na kt�re s� wysy�ane komunikaty kompilacji.

@note Aby wszystkie definicje si� za��czy�y trzeba zadba�, aby makro @ref SHOW_MEMORY_LEAKS w pliku
@ref macros_switches.h by�o zdefiniowane.
Je�eli @ref macros_switches.h nie jest includowany, to trzeba gdzie� samemu to makro zdefiniowa�.
*/

#ifdef SHOW_MEMORY_LEAKS
	#define _CRTDBG_MAP_ALLOC
	#include <cstdlib>
	#include <crtdbg.h>

	#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW

#endif