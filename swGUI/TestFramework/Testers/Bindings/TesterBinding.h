#pragma once

#include "swGUI/Core/System/DataBinding/Binding.h"

#include "swGUI/Core/System/DataBinding/Converters/IValueConverter.h"


namespace sw {
namespace gui
{

// ================================ //
//
class CLASS_TESTER( Binding )
{
protected:

	// ================================ //
	//
	Nullable< void >	ValidateBinding			( Binding& binding, TypeID srcType, TypeID targetType )
	{
		return binding.ValidateBinding( srcType, targetType );
	}

	// ================================ //
	//
	void				SetConverter			( Binding& binding, IValueConverter* converter )
	{
		binding.SetConverter( converter );
	}
};


// ================================ //
//
class MockConverter : public IValueConverter
{
private:

	bool		m_forwardConversion;
	bool		m_backwardConversion;

public:

	void		SetConversionResult		( bool forward, bool backward )
	{
		m_forwardConversion = forward;
		m_backwardConversion = backward;
	}


public:

	virtual rttr::variant	Convert				( const rttr::variant& object, TypeID targetType, const rttr::variant& params, const CultureInfo* culture ) const override;
	virtual rttr::variant	ConvertBack			( const rttr::variant& object, TypeID targetType, const rttr::variant& params, const CultureInfo* culture ) const override;
	
	virtual bool			CanConvert			( TypeID srcType, TypeID targetType ) const override;
	virtual bool			CanConvertBack		( TypeID srcType, TypeID targetType ) const override;

};

}	// gui
}	// sw

