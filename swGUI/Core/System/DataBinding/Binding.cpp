#include "Binding.h"

#include "swCommonLib/Common/Properties/Properties.h"



namespace sw {
namespace gui
{


// ================================ //
//
Binding::Binding		( BindingExpressionPtr expression, const rttr::variant & target, const rttr::property & targetProperty )
	: m_expression( expression )
	, m_sourceProperty( Properties::EmptyProperty() )
	, m_targetProperty( targetProperty )
	, m_mode( BindingMode::OneWay )
	, m_updateTrigger( UpdateSourceTrigger::Default )
{
	SetConverter( nullptr );
	SetValidator( nullptr );
}

// ================================ //
//
Nullable< void >		Binding::UpdateBinding		( const rttr::variant& target, const rttr::variant& dataContext )
{
	auto bindingSource = m_expression->EvaluateExpression( dataContext, target );
	
	if( bindingSource.IsValid() )
	{
		m_sourceObject = bindingSource.Get().Target;
		m_sourceProperty = bindingSource.Get().Property;

		return Result::Success;
	}

	return Result::Error;
}

// ================================ //
//
void					Binding::SetConverter		( IValueConverter* converter )
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
void					Binding::SetValidator		( IValueValidator* validator )
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
Nullable< void >	Binding::ValidateBinding			( TypeID srcType, TypeID targetType )
{
	bool toSource = IsDirectionToSource( m_mode );
	bool toTarget = IsDirectionToTarget( m_mode );

	assert( toSource || toTarget );

	bool valid = true;

	// If converter exist, we don't try normal conversion path.
	if( m_useConverter && m_converter )
	{
		valid = toTarget ? valid && ValidateConverter( srcType, targetType ) : valid;
		valid = toSource ? valid && ValidateConverterBack( targetType, srcType ) : valid;

		///< @todo Add exceptions.
		return valid ? Result::Success : Result::Error;
	}

	valid = toTarget ? valid && srcType.is_derived_from( targetType ) : valid;
	valid = toSource ? valid && targetType.is_derived_from( srcType ) : valid;

	if( valid ) return Result::Success;

	valid = true;
	valid = toTarget ? valid && ValidateAutoConversion( srcType, targetType ) : valid;
	valid = toSource ? valid && ValidateAutoConversion( targetType, srcType ) : valid;

	if( valid ) return Result::Success;
	return Result::Error;
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




}	// gui
}	// sw


