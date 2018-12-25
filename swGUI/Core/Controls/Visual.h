#pragma once
/**
@file Visual.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGUI/Core/System/DataBinding/DependencyObject.h"
#include "swGUI/Core/System/CommonTypes/CommonTypes.h"
#include "swGUI/Core/System/CommonTypes/AccessKey.h"

#include "swGUI/Core/System/Rendering/Drawings/IDrawing.h"


namespace sw {
namespace gui
{


/**@brief Provide interface for visual controls which can be rendered.

Provides interfaces and base implementation of:
- HitTesting
- Rendering

This classs correpsonds to WPF Visual class.
@ingroup ControlsFramework*/
class Visual : public DependencyObject
{
	RTTR_ENABLE( DependencyObject );
	RTTR_REGISTRATION_FRIEND;
private:

	Position		m_offset;		///< Control position relative to parent.

protected:


public:
	explicit		Visual		() = default;
	virtual			~Visual		() = default;

	/**@brief Checks if point is within this object.
	@todo We must specify if point is in relative coordinates or absolut.*/
	virtual bool					HitTest				( const Point& point )			= 0;

	/**@brief Get number of children in visual tree.*/
	virtual Size					GetNumChildren		() const						= 0;
	
	/**@brief Gets child in visual tree.*/
	virtual Visual*					GetVisualChild		( Size idx ) const				= 0;

public:

	/**@brief Gets Drawing object for this control.
	Drawing object gives Visual it's appearance.*/
	virtual const IDrawingPtr&		QueryDrawing		() const						= 0;

};



}	// gui
}	// sw


