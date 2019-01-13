#pragma once

#include "DX11Utils.h"


//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename FactoryType>
inline ComPtr< FactoryType >		DX11Utils::GetFactory		()
{
	HRESULT result;

	ComPtr< IDXGIAdapter > dxgiAdapter = DX11Utils::GetDXGIAdapter();
	if( dxgiAdapter )
	{
		ComPtr< FactoryType > dxgiFactory = nullptr;
		result = dxgiAdapter->GetParent( __uuidof( FactoryType ), (void **)&dxgiFactory );

		assert( SUCCEEDED( result ) );
		if( FAILED( result ) )	return nullptr;

		return dxgiFactory;
	}

	return nullptr;
}

