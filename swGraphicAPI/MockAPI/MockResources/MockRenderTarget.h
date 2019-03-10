#pragma once

#include "swGraphicAPI/Resources/MeshResources.h"


namespace sw
{



/**@brief
@ingroup MockAPI*/
class MockRenderTarget : public RenderTargetObject
{
	RTTR_ENABLE( RenderTargetObject );
private:

	uint16							m_height;
	uint16							m_width;

protected:
	~MockRenderTarget();
public:
	MockRenderTarget( Texture* colorBuffer,
					  Texture* depthBuffer,
					  Texture* stencilBuffer );


	inline uint16							GetWidth() { return m_width; }
	inline uint16							GetHeight() { return m_height; }
	inline void								SetHeight		( uint16 value ) { m_height = value; }
	inline void								SetWidth		( uint16 value ) { m_width = value; }

	static MockRenderTarget*				CreateScreenRenderTarget();
	static MockRenderTarget*				CreateRenderTarget( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor );

private:
	static bool								ValidateDescriptor( const RenderTargetDescriptor& renderTargetDescriptor );
};

}	// sw
