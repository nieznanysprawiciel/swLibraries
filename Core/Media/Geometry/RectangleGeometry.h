#pragma once
/**
@file RectangleGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/Media/Geometry/Geometry.h"


namespace sw {
namespace gui
{


/**@brief Generates Rectangle.
@ingroup Geometries*/
class RectangleGeometry : public Geometry
{
private:
protected:

	float				m_width;
	float				m_height;
	float				m_strokeThickness;

public:

	explicit		RectangleGeometry		();
	virtual			~RectangleGeometry		() = default;

	void				SetWidth			( float width );
	void				SetHeight			( float height );
	void				SetThickness		( float thickness );

public:

	// Inherited via Geometry
	virtual bool				HitTest				( const Point& point )		override;
	virtual bool				HitTest				( const Rect& rectangle )	override;
	virtual GeometryData		Generate			()							override;
	virtual BufferRange			BufferData			()							override;
	virtual std::string			ShaderFunctionFile	()							override;
	virtual std::wstring		GeometryName		()							override;
	virtual std::wstring		ConstantsName		()							override;

};




}	// gui
}	// sw


