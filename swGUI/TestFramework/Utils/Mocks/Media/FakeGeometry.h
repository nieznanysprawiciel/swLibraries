#pragma once
/**
@file FakeGeometry.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/Media/Geometry/Geometry.h"

#include "swCommonLib/Common/Buffers/StackBuffer.h"


namespace sw {
namespace gui
{




/**@brief Mock geometry for tests.*/
class FakeGeometry : public Geometry
{
public:

	struct Variables
	{
		float			Height;
		float			Width;
	};

private:
protected:

	std::string			    m_geomName;
	std::string				m_shaderFun;

	StackBufferA< Variables >	m_buffer;

public:
	explicit		FakeGeometry		( Geometry::ConstantBufferMode cbMode );
	virtual			~FakeGeometry		() = default;


public:

	virtual bool			    HitTest			( const Point& point ) const override;
	virtual bool			    HitTest			( const Rect& rectangle ) const override;

	virtual Nullable< GeometryData >	Generate		() override;
	virtual BufferRange					BufferData		() override;

	virtual fs::Path			ShaderFunctionFile	() override;
	virtual std::string	        GeometryName		() override;
	virtual AssetPath	        ConstantsName		() override;

public:

	using Geometry::NeedsShaderUpdate;
	using Geometry::NeedsConstantsUpdate;
	using Geometry::NeedsGeometryUpdate;

	void					ChangeGeometry		( const std::string& geomName );
	void					SetShaderFunction	( const std::string& shaderFun );

	void					SetHeight			( float height );
	void					SetWidth			( float width );
};

DEFINE_PTR_TYPE( FakeGeometry )



}	// gui
}	// sw


