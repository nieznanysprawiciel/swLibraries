#pragma once
/**
@file DX11DebugLayer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <string>

#pragma warning( disable : 4005 )
//#include "d3dx11.h"
#include <d3d11.h>
#pragma warning( default : 4005 )


namespace sw
{


/**@brief Debug functionalities.*/
class DX11DebugLayer
{
private:
protected:
public:
	explicit		DX11DebugLayer		() = default;
					~DX11DebugLayer		() = default;

public:

	void			SetDebugName		( ID3D11DeviceChild* child, const std::string& name );
};



}	// sw


