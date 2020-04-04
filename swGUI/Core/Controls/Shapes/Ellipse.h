#pragma once
/**
@file Ellipse.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "Shape.h"




namespace sw {
namespace gui
{

/**@brief Draws ellipse shape.
@ingroup Shapes
@ingroup Controls*/
class Ellipse : public Shape
{
	RTTR_ENABLE( Shape );
	RTTR_REGISTRATION_FRIEND;
private:

	float				m_strokeThickness;

protected:
public:

	explicit		Ellipse			();
	virtual			~Ellipse		() = default;


    virtual void        SetWidth			( float width ) override;
    virtual void        SetHeight			( float height ) override;
	void				SetThickness		( float thickness );

};

DEFINE_OPTR_TYPE( Ellipse );


}	// gui
}	// sw


