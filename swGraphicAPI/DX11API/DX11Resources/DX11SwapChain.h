#pragma once
/**
@file DX11SwapChain.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/




#include "swGraphicAPI/DX11API/DX11Initializer/DX11APIObjects.h"
#include "swGraphicAPI/Resources/SwapChain.h"
#include "DX11RenderTarget.h"




namespace sw
{


// ================================ //
//
class DX11SwapChain : public SwapChain, protected DX11APIObjects
{
	RTTR_ENABLE( SwapChain )
private:

	IDXGISwapChain*			m_swapChain;

public:
	DX11SwapChain( IDXGISwapChain* chain, DX11RenderTarget* windowRT );
	~DX11SwapChain();

	virtual void			Present			( int syncInterval )					override;
	virtual void			Resize			( uint16 newWidth, uint16 newHeight )	override;

public:
	static DX11SwapChain*	CreateScreenSwapChain	( RenderTarget* screenRT );
};


}	// sw