#pragma once
/**
@file DX11RenderTarget.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swGraphicAPI/Resources/MeshResources.h"
#include "DX11Initializer/DX11APIObjects.h"



namespace sw
{


/**@brief DirecX 11 implementation of render target.
@ingroup DX11API*/
class DX11RenderTarget : public RenderTarget, protected DX11APIObjects
{
	RTTR_ENABLE( RenderTarget );
private:
	ComPtr< ID3D11RenderTargetView >	m_renderTarget;
	ComPtr< ID3D11DepthStencilView >	m_depthStencilView;

	uint16							m_height;
	uint16							m_width;
protected:
	~DX11RenderTarget();
public:
	DX11RenderTarget( ComPtr< ID3D11RenderTargetView > renderTarget,
					  ComPtr< ID3D11DepthStencilView > depthStencil,
					  Texture* colorBuffer,
					  Texture* depthBuffer,
					  Texture* stencilBuffer );


	inline uint16							GetWidth() { return m_width; }
	inline uint16							GetHeight() { return m_height; }
	inline void								SetHeight		( uint16 value ) { m_height = value; }
	inline void								SetWidth		( uint16 value ) { m_width = value; }

	inline ID3D11RenderTargetView*			GetRenderTarget() { return m_renderTarget.Get(); }
	inline ID3D11DepthStencilView*			GetDepthStencil() { return m_depthStencilView.Get(); }

	static DX11RenderTarget*				CreateScreenRenderTarget();
	static DX11RenderTarget*				CreateRenderTarget( const std::wstring& name, const RenderTargetDescriptor& renderTargetDescriptor );

private:
	static bool								ValidateDescriptor( const RenderTargetDescriptor& renderTargetDescriptor );
};



}	// sw
