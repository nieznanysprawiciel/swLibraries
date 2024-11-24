#pragma once
/**
@file Dir.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Path.h"

#include <vector>


namespace sw {
namespace fs
{


/**@brief Directory manipulation.*/
class Dir
{
private:
protected:
public:
	explicit		Dir() = default;
	~Dir() = default;


	static bool					CreateDirectory		( const sw::fs::Path& path );
    static std::vector< Path >	ListFiles			( const sw::fs::Path& path );
};

}
}
