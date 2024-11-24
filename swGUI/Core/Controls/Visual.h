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

class sw::ResourceManagerAPI;


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
    Size2D          m_size;         ///< Size of control (bounding box).

protected:


public:

	explicit		Visual		();
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
	virtual IDrawing*				QueryDrawing		() const						= 0;

	/**@brief Updates underlying @ref IDrawing object's Resources.
	
	This function's prupose is to allow deferred reloading of heavier Resources. There is
	another function (@ref IDrawing::RebuildResources) that serves the same purpose.
	The main difference is, that Visual::UpdateDrawing allows doing this on Visual control
	level.

	The best example illustrating purpose is @ref TextBlock control. There are several
	properties that decide what @ref FontAsset should be loaded for unrelying @ref TextDrawing:
	FontStyle, FontWeight and FontFamily. If @ref FontAsset would be loaded immediately,
	changing all three properties would trigger loading Font 3 times.
	This could be avoided if all 3 parameters would be avaiable on @ref TextDrawing level,
	but such a solution would force repeating all parameters in TextDrawing and TextBlock
	and would prevent from creating higher level abstractions that use simpler bulding blocks.*/
    virtual ReturnResult			UpdateDrawingResources( sw::ResourceManagerAPI& resourceManager ){ return Success::True; };

	Position						GetVisualOffset		() const { return m_offset; }
    Size2D                          GetSize             () const { return m_size; }

public:
	// Temporary
	void							SetOffset			( Position pos ) { m_offset = pos; }
    virtual void				    SetWidth			( float width );
    virtual void				    SetHeight			( float height );
};



}	// gui
}	// sw


