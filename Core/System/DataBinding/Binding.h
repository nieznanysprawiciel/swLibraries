#pragma once
/**
@file Binding.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "BindingMode.h"

#include "Expressions/BindingExpression.h"

#include "Converters/IValueConverter.h"
#include "Validators/IValueValidator.h"

#include <string>
#include <vector>



namespace sw {
namespace gui
{

class Binding;
DEFINE_PTR_TYPE( Binding )



/**@brief Holds information about single binding.

@todo Consider supporting asynchronous binding.
@todo Consider using this object as unique pointer instead of shared pointer.

@ingroup DataBindingSystem*/
class Binding
{
	FRIEND_CLASS_TESTER( Binding )
protected:

	rttr::property			m_sourceProperty;
	rttr::variant			m_sourceObject;
	rttr::property			m_targetProperty;
	rttr::variant			m_targetObject;

	BindingMode				m_mode;
	UpdateSourceTrigger		m_updateTrigger;

	bool					m_useConverter : 1;		
	bool					m_useValidation : 1;		///< Optimization: Don't try to access Validator since it can be in another cache line.

	bool					m_bindObject : 1;			///< Tells to bind object instead property in case that property is invalid.
	bool					m_validConversion : 1;		///< True if property can be converted. Otherwise default value will be used to synchronize values.

	IValueConverter*		m_converter;
	IValueValidator*		m_validator;

	BindingExpressionPtr	m_expression;				///< Use BindingExpression to retrive binding info when DataContext changes.

public:

	explicit			Binding				( const rttr::property& targetProperty, const rttr::variant& target, BindingExpressionPtr expression );


	/**@brief Updates source object nd property based on BindingExpression.*/
	ReturnResult		UpdateBinding		( const rttr::variant& dataContext );

	/**@brief Propagates value from parameter to Source property.
	This function doesn't check Target property value*/
	void				PropagateToSource	( const rttr::variant& value );
	bool				PropagateToTarget	( const rttr::variant& value );

	/**@brief Propagates value from parameter to Source property.
	This function gets value from Target property.*/
	void				PropagateToSource	();
	bool				PropagateToTarget	();

	rttr::variant		GetValue			() const;
	rttr::variant		GetSourceValue		() const;

public:

	///@name Creation functions
	///@{
	static BindingPtr	Create				( const rttr::property& targetProperty, const rttr::variant& target, BindingExpressionPtr expression );
	static BindingPtr	Create				( const rttr::property& targetProperty, const rttr::variant& target, BindingExpressionPtr expression, BindingMode mode );
	
	/**@brief Creates binding.
	@param[in] expression Function uses path from expression parameter to create DefaultBindingExpression.
	@param[in] target Target object whose property will be bound.
	@param[in] property Function gets TypeID from target and searches it's properties to find name passed in this parameter.*/
	static BindingPtr	Create				( const std::string& property, const rttr::variant& target, const std::string& expression );
	static BindingPtr	Create				( const std::string& property, const rttr::variant& target, const std::string& expression, BindingMode mode );

	
	
	///@}

private:

	void				SetConverter	( IValueConverter* converter );
	void				SetValidator	( IValueValidator* validator );


	/**@brief Checks if properties are compatibile.
	Function calls CheckCompatibility and passes @ref Binding members to it.*/
	ReturnResult		CheckCompatibility		();

	/**@brief Checks if properties are compatibile.
	Function determines if bound properties can be really bound by calling ValidateBinding. Then it sets internal flags which will be used
	during property value evaluation. This should precompute all posible things to optimise future evaluations time.*/
	ReturnResult		CheckCompatibility		( const rttr::property& targetProperty, const rttr::property& srcProperty, const rttr::variant& srcObject );

	/**@brief Validates binding between properties.
	
	@param[in] srcType Type of SourceProperty or SourceObject in case we bind to object instead of property.
	@param[in] targetType Type of TargetProperty

	Evaluation order:
	- Check if types are all wrappers or raw. Can't mix these options.
	- Check if converter can convert srcType to targetType. Next steps are performed only if converter is nullptr.
	- Check if srcType is derived from targetType (in case of basic types it checks if are equal).
	- Check if automatic conversion can be made.
	
	Evaluation order for @ref BindingMode::TwoWay:
	- Check if types are all wrappers or raw. Can't mix these options.
	- Check if converter can convert types fort and back. Next steps are performed only if converter is nullptr.
	- Check if types are equal.
	- Check if automatic conversion can be made.

	@Note If this Validation fails, binding will return default value for these properties binding.*/
	ReturnResult		ValidateBinding			( TypeID srcType, TypeID targetType );

	bool				ValidateConverter		( TypeID srcType, TypeID targetType );
	bool				ValidateConverterBack	( TypeID srcType, TypeID targetType );
	bool				ValidateAutoConversion	( TypeID srcType, TypeID targetType );


	bool				IsDirectionToSource		( BindingMode mode );
	bool				IsDirectionToTarget		( BindingMode mode );

public:

	IValueConverter*		GetConverter			() const { return m_converter; }
	IValueValidator*		GetValidator			() const { return m_validator; }

	BindingMode				GetBindingMode			() const { return m_mode; }
	UpdateSourceTrigger		GetUpdateTrigger		() const { return m_updateTrigger; }

	BindingExpressionPtr	GetBindingExpression	() const { return m_expression; }

	rttr::property			GetSourceProperty		() const { return m_sourceProperty; }
	rttr::property			GetTargetProperty		() const { return m_targetProperty; }
	rttr::variant			GetSourceObject			() const { return m_sourceObject; }

	void					SetBindingMode			( BindingMode mode ) { m_mode = mode; }
	void					SetUpdateTrigger		( UpdateSourceTrigger updateTrigger ) { m_updateTrigger = updateTrigger; }
};



}	// gui
}	// sw



