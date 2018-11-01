#pragma once
/**
@file DrawingTester.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/TypesDefinitions.h"
#include "swGUI/Core/System/Rendering/Drawings/Drawing.h"




namespace sw {
namespace gui
{

// ================================ //
//
class CLASS_TESTER( Drawing )
{
public:

	static impl::GeometryRenderingData&				GetGeometryRenderingData	( Drawing* drawing ) { return drawing->m_geometryData; }
	static impl::BrushRenderingData&				GetBrushRenderingData		( Drawing* drawing ) { return drawing->m_brushData; }
	static impl::BrushRenderingData&				GetPenRenderingData			( Drawing* drawing ) { return drawing->m_penData; }

};



}	// gui
}	// sw

