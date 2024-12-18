/**
@file Binding.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "Binding.h"

#include "swCommonLib/Common/Properties/Properties.h"

#include "swGUI/Core/System/DataBinding/Expressions/DefaultBindingExpression.h"

#include "Exceptions/InvalidBindingException.h"



namespace sw {
namespace gui
{


// ================================ //
//
Binding::Binding		( const rttr::property& targetProperty, const rttr::variant& target, BindingExpressionPtr expression )
	: m_expression( expression )
	, m_sourceProperty( Properties::EmptyProperty() )
	, m_targetProperty( targetProperty )
	, m_targetObject( target )
	, m_mode( BindingMode::OneWay )
	, m_updateTrigger( UpdateSourceTrigger::Default )
{
	SetConverter( nullptr );
	SetValidator( nullptr );
}

// ================================ //
//
ReturnResult			Binding::UpdateBinding			( const rttr::variant& dataContext )
{
	auto bindingSource = m_expression->EvaluateExpression( dataContext, m_targetObject );
	
	if( bindingSource.IsValid() )
	{
		m_sourceObject = bindingSource.Get().Target;
		m_sourceProperty = bindingSource.Get().Property;

		return Success::True;
	}

	return Success::False;
}

// ================================ //
//
void					Binding::PropagateToSource		( const rttr::variant& value )
{
	if( IsDirectionToSource( m_mode ) )
		m_sourceProperty.set_value( m_sourceObject, value );
}

// ================================ //
//
bool					Binding::PropagateToTarget		( const rttr::variant& value )
{
	if( IsDirectionToTarget( m_mode ) )
	{
		m_targetProperty.set_value( m_targetObject, value );
		return true;
	}

	return false;
}

// ================================ //
//
void					Binding::PropagateToSource		()
{
	rttr::variant value = GetValue();
	PropagateToSource( value );
}

// ================================ //
//
bool					Binding::PropagateToTarget		()
{
	rttr::variant value = GetSourceValue();
	
	// Propagate value only if something changes.
	if( value == GetValue() )
		return false;

	return PropagateToTarget( value );
}

// ================================ //
//
rttr::variant			Binding::GetSourceValue			() const
{
	return m_sourceProperty.get_value( m_sourceObject );
}

// ================================ //
//
rttr::variant			Binding::GetValue				() const
{
	return m_targetProperty.get_value( m_targetObject );
}


// ================================ //
//
void					Binding::SetConverter			( IValueConverter* converter )
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
void					Binding::SetValidator			( IValueValidator* validator )
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

// ================================ //
//
ReturnResult		Binding::CheckCompatibility			()
{
	return CheckCompatibility( m_targetProperty, m_sourceProperty, m_sourceObject );
}

// ================================ //
//
ReturnResult		Binding::CheckCompatibility			( const rttr::property& targetProperty, const rttr::property& srcProperty, const rttr::variant& srcObject )
{
	// Reset values.
	m_bindObject = false;
	m_validConversion = false;

	// This shouldn't happen.
	if( !targetProperty.is_valid() )
		return "[Binding] Target property is invalid. This indicates error in code.";

	TypeID srcType = srcProperty.get_type();
	TypeID dstType = targetProperty.get_type();

	// If property is invalid we bind source object. This isn't handling of invalid case.
	// In some situations expressions can return only source object (while accessing array for example).
	if( !srcProperty.is_valid() )
	{
		srcType = srcObject.get_type();
		m_bindObject = true;
	}

	if( !ValidateBinding( srcType, dstType ).IsValid() )
		return std::make_shared< InvalidBindingException >( srcType, dstType );

	m_validConversion = true;

	return Success::True;
}

// ================================ //
//
bool				Binding::IsDirectionToSource		( BindingMode mode )
{
	return m_mode == BindingMode::OneWayToSource || m_mode == BindingMode::TwoWay;
}

// ================================ //
//
bool				Binding::IsDirectionToTarget		( BindingMode mode )
{
	return m_mode == BindingMode::OneWay || m_mode == BindingMode::TwoWay || m_mode == BindingMode::OneTime;
}

// ================================ //
//
ReturnResult		Binding::ValidateBinding			( TypeID srcType, TypeID targetType )
{
	bool toSource = IsDirectionToSource( m_mode );
	bool toTarget = IsDirectionToTarget( m_mode );

	assert( toSource || toTarget );

	bool valid = true;

	// Both types should be raw or wrapped. We can't support mixed types.
	if( srcType.is_wrapper() != targetType.is_wrapper() )
		return Success::False;

	// If converter exist, we don't try normal conversion path.
	if( m_useConverter && m_converter )
	{
		valid = toTarget ? valid && ValidateConverter( srcType, targetType ) : valid;
		valid = toSource ? valid && ValidateConverterBack( targetType, srcType ) : valid;

		///< @todo Add exceptions.
		return valid ? Success::True : Success::False;
	}

	valid = toTarget ? valid && srcType.is_derived_from( targetType ) : valid;
	valid = toSource ? valid && targetType.is_derived_from( srcType ) : valid;

	if( valid ) return Success::True;

	valid = true;
	valid = toTarget ? valid && ValidateAutoConversion( srcType, targetType ) : valid;
	valid = toSource ? valid && ValidateAutoConversion( targetType, srcType ) : valid;

	if( valid ) return Success::True;
	return Success::False;
}

// ================================ //
//
bool				Binding::ValidateConverter			( TypeID srcType, TypeID targetType )
{
	if( m_useConverter && m_converter )
	{
		return m_converter->CanConvert( srcType, targetType );
	}

	return false;
}

// ================================ //
//
bool				Binding::ValidateConverterBack		( TypeID srcType, TypeID targetType )
{
	if( m_useConverter && m_converter )
	{
		return m_converter->CanConvertBack( srcType, targetType );
	}

	return false;
}

// ================================ //
//
bool				Binding::ValidateAutoConversion		( TypeID srcType, TypeID targetType )
{
	// RTTR makes automatic conversion for arithmetic types for us.
	return srcType.is_arithmetic() && targetType.is_arithmetic();
}

//====================================================================================//
//			Creation functions	
//====================================================================================//


// ================================ //
//
BindingPtr			Binding::Create						( const rttr::property& targetProperty, const rttr::variant& target, BindingExpressionPtr expression )
{
	return std::make_shared< gui::Binding >( targetProperty, target, expression );
}

// ================================ //
//
BindingPtr			Binding::Create						( const rttr::property& targetProperty, const rttr::variant& target, BindingExpressionPtr expression, BindingMode mode )
{
	auto binding = Create( targetProperty, target, expression );
	binding->SetBindingMode( mode );

	return binding;
}

// ================================ //
//
BindingPtr			Binding::Create						( const std::string& property, const rttr::variant& target, const std::string& expression )
{
	gui::DefaultBindingExpressionPtr defaultExpression = std::make_shared< gui::DefaultBindingExpression >( expression );

	TypeID type = Properties::GetRealType( target );
	rttr::property prop = type.get_property( property );

	return Create( prop, target, defaultExpression );
}

// ================================ //
//
BindingPtr			Binding::Create						( const std::string& property, const rttr::variant& target, const std::string& expression, BindingMode mode )
{
	auto binding = Create( property, target, expression );
	binding->SetBindingMode( mode );

	return binding;
}



}	// gui
}	// sw


