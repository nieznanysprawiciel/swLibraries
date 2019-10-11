#pragma once
/**
@file FakeDrawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"


namespace sw {
namespace gui
{


/**@brief Drawing for tests.*/
class FakeDrawing : public Drawing
{
private:
protected:
public:
	explicit		FakeDrawing		() = default;
	virtual			~FakeDrawing	() = default;

public:

	using Drawing::UpdateBrushShader;
	using Drawing::UpdateBrushTexture;
	using Drawing::UpdateBrushConstants;

	using Drawing::UpdatePenShader;
	using Drawing::UpdatePenTexture;
	using Drawing::UpdatePenConstants;

	using Drawing::UpdateVertexShader;
	using Drawing::UpdateGeometry;
	using Drawing::UpdateGeometryConstants;

	using Drawing::CreateAndSetLayout;

public:

	
	virtual void			Render					( IRenderer* renderer ) override;
	virtual void			RebuildResources		( ResourceManagerAPI resourceManager, ShaderProvider* sp );

};

DEFINE_PTR_TYPE( FakeDrawing )

}	// gui
}	// sw

