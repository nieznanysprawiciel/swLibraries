#pragma once

#include "swGraphicAPI/Resources/MeshResources.h"


typedef void*	WindowHandler;




namespace sw
{


/**@brief Descripto of SwapChain
@ingroup Resources*/
struct SwapChainDescriptor
{
	WindowHandler			WindowHandle;
	unsigned short			Width;
	unsigned short			Height;
	ResourceFormat			Format;
	uint8					SamplesCount;
	uint8					SamplesQuality;
	bool					AllowFullscreen;
	uint8					NumBuffers;


	SwapChainDescriptor()
		: SamplesCount( 1 )
		, SamplesQuality( 0 )
		, AllowFullscreen( true )
		, Format( ResourceFormat::RESOURCE_FORMAT_R8G8B8A8_UNORM )
		, WindowHandle( nullptr )
		, NumBuffers( 1 )
	{}
};


/**@brief 
@ingroup Resources*/
class SwapChain : public Resource
{
	RTTR_ENABLE()
protected:

	ResourcePtr< RenderTarget >	m_renderTarget;

protected:
	SwapChain( RenderTarget* windowRT )
		: Resource( WRONG_ID )
		, m_renderTarget( windowRT )
	{
		assert( windowRT );
	}

public:
	virtual ~SwapChain()
	{}


	virtual void			Present			( int syncInterval ) = 0;
	virtual void			Resize			( uint16 newWidth, uint16 newHeight ) = 0;


	ResourcePtr< RenderTarget >		GetRenderTarget	() { return m_renderTarget; }

	// Inherited via Resource
	virtual std::string		GetResourceName	() const override { return "SwapChain: " + m_renderTarget->GetResourceName(); }
};


}	// sw