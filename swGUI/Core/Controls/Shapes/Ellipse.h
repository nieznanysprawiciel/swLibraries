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

	float				m_width;				///< Remove in future. This should be implemented in ArrangeCore.
	float				m_height;				///< Remove in future. This should be implemented in ArrangeCore.
	float				m_strokeThickness;

protected:
public:

	explicit		Ellipse			();
	virtual			~Ellipse		() = default;


	void				SetWidth			( float width );
	void				SetHeight			( float height );
	void				SetThickness		( float thickness );

};

DEFINE_OPTR_TYPE( Ellipse );


}	// gui
}	// sw


