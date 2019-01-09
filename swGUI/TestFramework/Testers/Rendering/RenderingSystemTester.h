#pragma once
/**
@file RenderingSystemTester.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/System/Rendering/RenderingSystem.h"

namespace sw {
namespace gui
{


// ================================ //
//
class CLASS_TESTER( RenderingSystem )
{
public:

	static RasterizerState*							GetRasterizerState			( RenderingSystem* system ) { return system->m_rasterizerState.Ptr(); }
	static DepthStencilState*						GetDepthStencilState		( RenderingSystem* system ) { return system->m_depthState.Ptr(); }
	static BlendingState*							GetTransparentBlendingState	( RenderingSystem* system ) { return system->m_transparentBlendState.Ptr(); }
	static BlendingState*							GetOpaqueBlendingState		( RenderingSystem* system ) { return system->m_opaqueBlendState.Ptr(); }
	static BufferObject*							GetRenderingSystemConsts	( RenderingSystem* system ) { return system->m_renderingSystemBuffer.Ptr(); }

};


}	// gui
}	// sw


