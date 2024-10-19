#pragma
/**
@file Escaping.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swSerialization/External/RapidXML/rapidxml.hpp"
#include "swSerialization/Interfaces/Serializer.h"

#include <string>


namespace sw
{

inline bool NeedsEscaping(const char* str)
{
    for (const char* ptr = str; *ptr != '\0'; ++ptr)
    {
        switch (*ptr)
        {
        case '&':
        case '<':
        case '>':
        case '"':
        case '\'':
            return true;
        }
    }

    return false;
}

inline std::string EscapeString(const std::string& name)
{
	std::string escapedString;
	escapedString.reserve(name.size());

	for (char c : name)
	{
		switch (c)
		{
		case '&':	escapedString += "&amp;"; break;
		case '<':	escapedString += "&lt;"; break;
		case '>':	escapedString += "&gt;"; break;
		case '"':	escapedString += "&quot;"; break;
		case '\'':	escapedString += "&apos;"; break;
		default:	escapedString += c; break;
		}
	}

	return escapedString;
}

/**@brief Returns escaped name allocated by rapidxml.

Escaping replaces single characters with few character strings, so it is not possible
to do it in place. Most strings don't need escaping, so it would be wasteful to make unnecessary
allocation. This function allocates only if there are characters that need escaping.*/
inline char* AllocateEscaped(rapidxml::xml_document<>& root, const std::string& name)
{
	if (NeedsEscaping(name.c_str()))
	{
		auto escapedString = EscapeString(name);
		return root.allocate_string(escapedString.c_str());
	}
	else
	{
		return root.allocate_string(name.c_str());
	}
}

} // namespace sw
