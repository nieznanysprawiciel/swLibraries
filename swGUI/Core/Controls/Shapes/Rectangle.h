#pragma once
/**
@file Rectangle.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Shape.h"


namespace sw {
namespace gui
{



/**@brief Draws rectangle shape.
@ingroup Shapes
@ingroup Controls*/
class Rectangle : public Shape
{
	RTTR_ENABLE( Shape );
	RTTR_REGISTRATION_FRIEND;
private:

	float				m_strokeThickness;

protected:
public:

	explicit		Rectangle		();
	virtual			~Rectangle		() = default;


	virtual void				SetWidth			( float width ) override;
	virtual void				SetHeight			( float height ) override;
	void				        SetThickness		( float thickness );

};

DEFINE_OPTR_TYPE( Rectangle );

}	// gui
}	// sw


