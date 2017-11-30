#include "Binding.h"

#include "swCommonLib/Common/Properties/Properties.h"



namespace sw {
namespace gui
{


// ================================ //
//
Binding::Binding		( BindingExpressionPtr expression )
	: m_expression( expression )
	, m_sourceProperty( Properties::EmptyProperty() )
	, m_targetProperty( Properties::EmptyProperty() )
	, m_mode( BindingMode::OneWay )
	, m_updateTrigger( UpdateSourceTrigger::Default )
{
	SetConverter( nullptr );
	SetValidator( nullptr );
}

// ================================ //
//
void		Binding::SetConverter		( IValueConverter* converter )
{
	if( converter )
	{
		m_converter = converter;
		m_useConverter = true;
	}
	else
	{
		m_useConverter = false;
		m_converter = nullptr;
	}
}

// ================================ //
//
void		Binding::SetValidator		( IValueValidator* validator )
{
	if( validator )
	{
		m_validator = validator;
		m_useValidation = true;
	}
	else
	{
		m_useValidation = false;
		m_validator = nullptr;
	}
}


}	// gui
}	// sw


