/**
@file DX11RenderTarget.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/
#include "swGraphicAPI/DX11API/stdafx.h"


#include "DX11RenderTarget.h"
#include "DX11Initializer/DX11ConstantsMapper.h"
#include "DX11Texture.h"

#include "swCommonLib/Common/MemoryLeaks.h"


RTTR_REGISTRATION
{
	rttr::registration::class_< sw::DX11RenderTarget >( "sw::DX11RenderTarget" );
}



namespace sw
{


/**@brief Zwalnia zasoby DirectXa.*/
DX11RenderTarget::~DX11RenderTarget()
{
	m_renderTarget = nullptr;
	m_depthStencilView = nullptr;
}



// ================================ //
//
DX11RenderTarget::DX11RenderTarget( const AssetPath& name,
									ComPtr< ID3D11RenderTargetView > renderTarget,
									ComPtr< ID3D11DepthStencilView > depthStencil,
									Texture* colorBuffer,
									Texture* depthBuffer,
									Texture* stencilBuffer )
	: RenderTarget( name, colorBuffer, depthBuffer, stencilBuffer )
	, m_renderTarget( renderTarget )
	, m_depthStencilView( depthStencil )
	, m_height( 0 )
	, m_width( 0 )
{}

/**Tworzy object DX11RenderTarget z bufora tylnego ekranu.

@todo Wersja troszkę niewłaściwa. RenderTarget jest już stworzony wcześniej przy zwykłej inicjalizacji DX11APIObjects.
Tutaj jest jedynie tworzony obiekt silnikowy, który potrafi to obsłużyć. Trzeba to zmienić, żeby całe tworzenie
render targetu odbywało się tutaj.

@note Wewnętrzne tekstury render targetu są ustawione na nullptr. Oznacza to, że nie można ich użyć w innych obiektach.
Zastanowić się czy to właściwe rozwiązanie i ewentualnie zmienić implementację.

@return Zwraca wskaźnik object DX11RenderTarget.*/
DX11RenderTarget*						DX11RenderTarget::CreateScreenRenderTarget()
{
	DX11RenderTarget* newRenderTarget = new DX11RenderTarget( AssetPath( "", SCREEN_RENDER_TARGET ), render_target, z_buffer_view, nullptr, nullptr, nullptr );

	// DX11RenderTarget created ComPtr and incremented references. That's why we decrement it here.
	render_target->Release();
	z_buffer_view->Release();

	render_target = nullptr;			// Ochrona przed podwójnym zwalnianiem obiektu.
	z_buffer_view = nullptr;			// Ochrona przed podwójnym zwalnianiem obiektu.

	auto viewPort = DX11APIObjects::get_viewport_desc();
	newRenderTarget->SetHeight( static_cast<uint16>( viewPort.Height ) );
	newRenderTarget->SetWidth( static_cast<uint16>( viewPort.Width ) );

	return newRenderTarget;
}

/**@brief Tworzy render target o podanych w parametrach.

@todo W przyszłości powinna być możliwość tworzenia tekstur innych niż 2D. Poza tym renderować
powinno się móc do dowolnego poziomu mipmap. Decyzja powinna być podejmowana w runtimie, więc
trzeba chyba stworzyć wiele widoków (???). Przydatne to jest w przypadku Environmental mappingu.
Jeżeli obiekt jest mocno oddalony, to nie ma co renderować mu mapy z dużą rozdzielczością.

@todo Split this function into smaller ones.*/
sw::Nullable< DX11RenderTarget* >		DX11RenderTarget::CreateRenderTarget			( const AssetPath& name, const RenderTargetDescriptor& renderTargetDescriptor )
{
	auto validation = ValidateDescriptor( renderTargetDescriptor );
	if( !validation.IsValid() )
		return validation.GetError();

	HRESULT result;

	ComPtr< ID3D11Texture2D > colorBuffer = nullptr;
	ComPtr< ID3D11Texture2D > depthStencilBuffer = nullptr;

	TextureInfo colorBufferInfo = renderTargetDescriptor.CreateTextureInfo();
	TextureInfo depthBufferInfo = renderTargetDescriptor.CreateTextureInfo();
	TextureInfo stencilBufferInfo = renderTargetDescriptor.CreateTextureInfo();


	unsigned int ArraySize = 1;
	if( renderTargetDescriptor.TextureType == TextureType::TextureArray2D || renderTargetDescriptor.TextureType == TextureType::TextureArray2DMultisample )
		ArraySize = renderTargetDescriptor.ArraySize;


	D3D11_TEXTURE2D_DESC renderTargetTexDesc;
	renderTargetTexDesc.Width = renderTargetDescriptor.Width;
	renderTargetTexDesc.Height = renderTargetDescriptor.Height;
	renderTargetTexDesc.MipLevels = 1;
	renderTargetTexDesc.Usage = DX11ConstantsMapper::Get( renderTargetDescriptor.Usage );
	renderTargetTexDesc.ArraySize = ArraySize;

	renderTargetTexDesc.SampleDesc.Count = 1;
	renderTargetTexDesc.SampleDesc.Quality = 0;
	if( renderTargetDescriptor.TextureType == TextureType::Texture2DMultisample || renderTargetDescriptor.TextureType == TextureType::TextureArray2DMultisample )
	{
		renderTargetTexDesc.SampleDesc.Count = renderTargetDescriptor.NumSamples;
		renderTargetTexDesc.SampleDesc.Quality = renderTargetDescriptor.SamplesQuality;
	}

	renderTargetTexDesc.MiscFlags = 0;
	if( renderTargetDescriptor.IsCubeMap )
		renderTargetTexDesc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
	if( renderTargetDescriptor.AllowShareResource )
		renderTargetTexDesc.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
	renderTargetTexDesc.CPUAccessFlags = 0;
	if( renderTargetDescriptor.CPURead )
		renderTargetTexDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_READ;
	if( renderTargetDescriptor.CPUWrite )
		renderTargetTexDesc.CPUAccessFlags |= D3D11_CPU_ACCESS_WRITE;

	// Wartości specyficzne dla bufora colorów.
	renderTargetTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	renderTargetTexDesc.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.ColorBuffFormat );

	result = device->CreateTexture2D( &renderTargetTexDesc, nullptr, &colorBuffer );
	if( result == S_OK )
	{
		// Wartości specyficzne dla bufora głębokości.
		renderTargetTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
		renderTargetTexDesc.Format = DX11ConstantsMapper::ConvertTypeless( renderTargetDescriptor.DepthStencilFormat );

		result = device->CreateTexture2D( &renderTargetTexDesc, nullptr, &depthStencilBuffer );
		if( result == S_OK )
		{
			ComPtr< ID3D11RenderTargetView >	renderTargetView;
			ComPtr< ID3D11DepthStencilView >	depthStencilView;

			D3D11_RENDER_TARGET_VIEW_DESC		renderTargetViewDescriptor;
			D3D11_DEPTH_STENCIL_VIEW_DESC		depthStencilViewDescriptor;
			D3D11_SHADER_RESOURCE_VIEW_DESC		shaderViewDescriptor;
			renderTargetViewDescriptor.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.ColorBuffFormat );
			renderTargetViewDescriptor.ViewDimension = DX11ConstantsMapper::Get( renderTargetDescriptor.TextureType );
			depthStencilViewDescriptor.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.DepthStencilFormat );
			depthStencilViewDescriptor.ViewDimension = DX11ConstantsMapper::ConvertDSV( renderTargetDescriptor.TextureType );
			depthStencilViewDescriptor.Flags = 0;			// Bufor głębokości lub stencilu do odczytu i zapisu.
			shaderViewDescriptor.ViewDimension = DX11ConstantsMapper::ConvertSRV( renderTargetDescriptor.TextureType );

			switch( renderTargetViewDescriptor.ViewDimension )
			{
				case D3D11_RTV_DIMENSION_TEXTURE2D:
					renderTargetViewDescriptor.Texture2D.MipSlice = 0;
					depthStencilViewDescriptor.Texture2D.MipSlice = 0;
					shaderViewDescriptor.Texture2D.MipLevels = -1;
					shaderViewDescriptor.Texture2D.MostDetailedMip = 0;
					break;
				case D3D11_RTV_DIMENSION_TEXTURE2DARRAY:
					renderTargetViewDescriptor.Texture2DArray.MipSlice = 0;
					renderTargetViewDescriptor.Texture2DArray.FirstArraySlice = 0;
					renderTargetViewDescriptor.Texture2DArray.ArraySize = ArraySize;
					depthStencilViewDescriptor.Texture2DArray.MipSlice = 0;
					depthStencilViewDescriptor.Texture2DArray.FirstArraySlice = 0;
					depthStencilViewDescriptor.Texture2DArray.ArraySize = ArraySize;
					shaderViewDescriptor.Texture2DArray.ArraySize = ArraySize;
					shaderViewDescriptor.Texture2DArray.FirstArraySlice = 0;
					shaderViewDescriptor.Texture2DArray.MipLevels = -1;
					shaderViewDescriptor.Texture2DArray.MostDetailedMip = 0;
					break;
				case D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY:
					renderTargetViewDescriptor.Texture2DArray.FirstArraySlice = 0;
					renderTargetViewDescriptor.Texture2DArray.ArraySize = 1;
					depthStencilViewDescriptor.Texture2DArray.FirstArraySlice = 0;
					depthStencilViewDescriptor.Texture2DArray.ArraySize = 1;
					shaderViewDescriptor.Texture2DMSArray.ArraySize = ArraySize;
					shaderViewDescriptor.Texture2DMSArray.FirstArraySlice = 0;
					break;
				case D3D11_RTV_DIMENSION_TEXTURE2DMS:
					break;		// Nic nie trzeba robić.
			}

			result = device->CreateRenderTargetView( colorBuffer.Get(), &renderTargetViewDescriptor, &renderTargetView );
			if( result == S_OK )
			{
				result = device->CreateDepthStencilView( depthStencilBuffer.Get(), &depthStencilViewDescriptor, &depthStencilView );
				if( result == S_OK )
				{
					ComPtr< ID3D11ShaderResourceView >	depthBufferResourceView = nullptr;
					ComPtr< ID3D11ShaderResourceView >	stencilBufferResourceView = nullptr;
					ComPtr< ID3D11ShaderResourceView >	colorBufferResourceView = nullptr;

					shaderViewDescriptor.Format = DX11ConstantsMapper::Get( renderTargetDescriptor.ColorBuffFormat );
					result = device->CreateShaderResourceView( colorBuffer.Get(), &shaderViewDescriptor, &colorBufferResourceView );
					if( result == S_OK )
					{
						shaderViewDescriptor.Format = DX11ConstantsMapper::ConvertDepthOnly( renderTargetDescriptor.DepthStencilFormat );
						result = device->CreateShaderResourceView( depthStencilBuffer.Get(), &shaderViewDescriptor, &depthBufferResourceView );
						if( result == S_OK )
						{
							shaderViewDescriptor.Format = DX11ConstantsMapper::ConvertStencilOnly( renderTargetDescriptor.DepthStencilFormat );
							if( shaderViewDescriptor.Format != DXGI_FORMAT_UNKNOWN )
								result = device->CreateShaderResourceView( depthStencilBuffer.Get(), &shaderViewDescriptor, &stencilBufferResourceView );
							if( result == S_OK )
							{
								colorBufferInfo.FilePath = name.GetInternalPath() / fs::Path( RENDER_TARGET_COLOR_BUFFER_NAME );
								colorBufferInfo.Format = renderTargetDescriptor.ColorBuffFormat;
								depthBufferInfo.FilePath = name.GetInternalPath() / fs::Path( RENDER_TARGET_DEPTH_BUFFER_NAME );
								depthBufferInfo.Format = DX11ConstantsMapper::ConvertBack( DX11ConstantsMapper::ConvertDepthOnly( renderTargetDescriptor.DepthStencilFormat ) );
								stencilBufferInfo.FilePath = name.GetInternalPath() / fs::Path( RENDER_TARGET_STENCIL_BUFFER_NAME );
								stencilBufferInfo.Format = DX11ConstantsMapper::ConvertBack( DX11ConstantsMapper::ConvertStencilOnly( renderTargetDescriptor.DepthStencilFormat ) );

								Texture* colorBufferTex = new DX11Texture( AssetPath( name.GetFile(), colorBufferInfo.FilePath ), std::move( colorBufferInfo ), colorBuffer.Get(), colorBufferResourceView );
								Texture* depthBufferTex = new DX11Texture( AssetPath( name.GetFile(), depthBufferInfo.FilePath ), std::move( depthBufferInfo ), depthStencilBuffer.Get(), depthBufferResourceView );
								Texture* stencilBufferTex = nullptr;
								if( stencilBufferResourceView != nullptr )
									stencilBufferTex = new DX11Texture( AssetPath( name.GetFile(), stencilBufferInfo.FilePath ), std::move( stencilBufferInfo ), depthStencilBuffer, stencilBufferResourceView );

								DX11RenderTarget* newRenderTarget = new DX11RenderTarget( name, renderTargetView, depthStencilView, colorBufferTex, depthBufferTex, stencilBufferTex );
								newRenderTarget->SetHeight( renderTargetDescriptor.Height );
								newRenderTarget->SetWidth( renderTargetDescriptor.Width );

								return newRenderTarget;
							}
						}
					}
				}
			}
		}
	}
	return "[DX11RenderTarget] Can't create render target.";
}

// ================================ //
//
ReturnResult							DX11RenderTarget::ValidateDescriptor		( const RenderTargetDescriptor& renderTargetDescriptor )
{
	TextureType RTType = renderTargetDescriptor.TextureType;
	if( RTType == TextureType::Texture1D ||
		RTType == TextureType::TextureArray1D ||
		RTType == TextureType::Texture3D ||
		RTType == TextureType::Buffer )
		return "[DX11RenderTarget] Can't create render target of type: " + TypeID::get< TextureType >().get_enumeration().value_to_name( RTType ).to_string();

	return Success::True;
}

}	// sw


