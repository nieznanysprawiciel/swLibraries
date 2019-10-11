#pragma once
/**
@file EllipseGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/Media/Geometry/Geometry.h"


namespace sw {
namespace gui
{


/**@brief Generates Ellipse.
@ingroup Geometries*/
class EllipseGeometry : public Geometry
{
private:
protected:

	float				m_width;
	float				m_height;
	float				m_strokeThickness;

public:

	explicit		EllipseGeometry		();
	virtual			~EllipseGeometry		() = default;

	void				SetWidth			( float width );
	void				SetHeight			( float height );
	void				SetThickness		( float thickness );

public:

	// Inherited via Geometry
	virtual bool				HitTest				( const Point& point )		override;
	virtual bool				HitTest				( const Rect& rectangle )	override;

	virtual GeometryData		Generate			()							override;
	virtual BufferRange			BufferData			()							override;

	virtual filesystem::Path    ShaderFunctionFile	()							override;
	virtual std::string		    GeometryName		()							override;
	virtual AssetPath		    ConstantsName		()							override;

};



}	// gui
}	// sw


