#pragma once
/**
@file CompilationException.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/Exceptions/Exception.h"


namespace sw
{

class CompilationException;
DEFINE_PTR_TYPE( CompilationException );



/**@brief Shader compilation failed.*/
class CompilationException : public RuntimeException
{
	RTTR_ENABLE( RuntimeException );
private:
protected:
public:
	explicit		CompilationException		( std::string compilationError );
	virtual			~CompilationException		() = default;

public:

	static CompilationExceptionPtr		Create			( std::string compilationError );
};


//====================================================================================//
//			Implementation	
//====================================================================================//


// ================================ //
//
inline CompilationException::CompilationException						( std::string compilationError )
	: RuntimeException( std::move( compilationError ) )
{}

// ================================ //
//
inline CompilationExceptionPtr		CompilationException::Create		( std::string compilationError )
{
	return std::make_shared< CompilationException >( std::move( compilationError ) );
}

}	// sw
