/**
@file MockSwapChain.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "MockSwapChain.h"




RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockSwapChain >( "sw::MockSwapChain" );
}


namespace sw
{

MockSwapChain::MockSwapChain( RenderTargetObject* screenRT )
	:	SwapChain( screenRT )
{}


MockSwapChain::~MockSwapChain()
{}


/**@copydoc SwapChain::Present.*/
void	MockSwapChain::Present( int syncInterval )
{
	//m_swapChain->Present( syncInterval, 0 );
}

/**@copydoc SwapChain::Resize.*/
void	MockSwapChain::Resize( uint16 newWidth, uint16 newHeight )
{
	assert( !"Implement me" );
}

/**@brief */
MockSwapChain* MockSwapChain::CreateScreenSwapChain( RenderTargetObject* screenRT )
{
	MockSwapChain* swapChainObject = new MockSwapChain( screenRT );
	return swapChainObject;
}

}	// sw