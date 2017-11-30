#pragma once
/**
@file Binding.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Engine.
*/


#include "swCommonLib/Common/RTTR.h"

#include "BindingMode.h"

#include "Expressions/BindingExpression.h"

#include "Converters/IValueConverter.h"
#include "Validators/IValueValidator.h"

#include <string>
#include <vector>



namespace sw {
namespace gui
{


/**@brief Holds information about single binding.

@todo Consider supporting asynchronous binding.

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

	IValueConverter*		m_converter;
	IValueValidator*		m_validator;

	BindingExpressionPtr	m_expression;				///< Use BindingExpression to retrive binding info when DataContext changes.

public:

	explicit		Binding			( BindingExpressionPtr expression );


private:

	void			SetConverter	( IValueConverter* converter );
	void			SetValidator	( IValueValidator* validator );


public:

	IValueConverter*		GetConverter			() const { return m_converter; }
	IValueValidator*		GetValidator			() const { return m_validator; }

	BindingMode				GetBindingMode			() const { return m_mode; }
	UpdateSourceTrigger		GetUpdateTrigger		() const { return m_updateTrigger; }

	BindingExpressionPtr	GetBindingExpression	() const { return m_expression; }

	rttr::property			GetSourceProperty		() const { return m_sourceProperty; }
	rttr::property			GetTargetProperty		() const { return m_targetProperty; }
	rttr::variant			GetSourceObject			() const { return m_sourceObject; }
	rttr::variant			GetTargetObject			() const { return m_targetObject; }

};

DEFINE_PTR_TYPE( Binding )


}	// gui
}	// sw



