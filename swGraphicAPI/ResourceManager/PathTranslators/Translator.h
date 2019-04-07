#pragma once
/**
@file Translator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <regex>


namespace sw
{

/**@brief Paths translation description.

First translator checks if path matches specified pattern (@ref m_matchPattern).
If it matches then it replaces all occurances of m_replacePattern with m_replaceExpression.

@deprecated Probably it isn't way to do what we want.*/
class Translator
{
private:

	std::regex			m_matchPattern;
	std::regex			m_replacePattern;
	std::string			m_replaceExpression;

protected:
public:
	explicit		Translator		() = default;
					~Translator		() = default;


	//bool			Apply			( std::string path );
};



}	// sw


