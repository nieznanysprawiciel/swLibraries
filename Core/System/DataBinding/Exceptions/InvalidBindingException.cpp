#include "InvalidBindingException.h"



namespace sw {
namespace gui
{

// ================================ //
//
InvalidBindingException::InvalidBindingException	( TypeID src, TypeID target )
	:	m_sourceType( src )
	,	m_targetType( target )
{}

// ================================ //
//
std::string			InvalidBindingException::ErrorMessage		() const
{
	return "Cannot bind source type [" + m_sourceType.get_name().to_string() + "] to target type [" + m_targetType.get_name().to_string() + "]. ";
}


}	// gui
}	// sw