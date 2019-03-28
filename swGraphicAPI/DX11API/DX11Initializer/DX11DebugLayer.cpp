/**
@file DX11DebugLayer.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/DX11API/stdafx.h"

#include "DX11DebugLayer.h"



namespace sw
{




// ================================ //
//
void				DX11DebugLayer::SetDebugName			( ID3D11DeviceChild* child, const std::string& name )
{
	if( child != nullptr )
	{
		child->SetPrivateData( WKPDID_D3DDebugObjectName, (uint32)name.size(), name.c_str() );
	}
}

}	// sw

