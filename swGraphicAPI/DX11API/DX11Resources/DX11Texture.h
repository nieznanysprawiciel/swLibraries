#pragma once
/**
@file DX11Texture.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Buffers/BufferRaw.h"

#include "DX11Initializer/DX11APIObjects.h"
#include "swGraphicAPI/Resources/MeshResources.h"


namespace sw
{


/**@brief DirectX 11 implementation of texture.
@ingroup DX11API*/
class DX11Texture : public sw::Texture, protected DX11APIObjects
{
	RTTR_ENABLE( Texture )
private:
	ComPtr< ID3D11ShaderResourceView >		m_textureView;
	ComPtr< ID3D11Texture2D >				m_texture;

	sw::TextureInfo							m_descriptor;
protected:
	~DX11Texture();
public:
	explicit								DX11Texture				( const AssetPath& name, sw::TextureInfo&& texInfo, ID3D11Texture2D* tex, ID3D11ShaderResourceView* texView );
	explicit								DX11Texture				( const AssetPath& name, sw::TextureInfo&& texInfo, ComPtr< ID3D11Texture2D > tex, ComPtr< ID3D11ShaderResourceView > texView );

	virtual bool							UpdateData				( uint8* dataPtr, uint16 mipLevel, uint16 arrayIdx ) override;
	virtual MemoryChunk						CopyData				() const override;
	virtual const sw::TextureInfo&			GetDescriptor			() const override;

	static sw::Nullable< DX11Texture* >		CreateFromMemory		( const AssetPath& name, const BufferRaw& texData, TextureInfo&& texInfo );
	static DX11Texture*						CreateFromMemory		( const MemoryChunk& texData, sw::TextureInfo&& texInfo );

	inline ID3D11ShaderResourceView*		Get			() { return m_textureView.Get(); }
	inline ID3D11Texture2D*					GetTex		() { return m_texture.Get(); }
	static D3D11_TEXTURE2D_DESC				FillDesc	( const sw::TextureInfo& texInfo );

private:

	uint16					MipWidth				( uint16 mipLevel ) const;
	uint16					MipHeight				( uint16 mipLevel ) const;
	uint32					MipRowSize				( uint16 mipLevel ) const;
	uint32					MipLevelSize			( uint16 mipLevel ) const;


private:
	void		Construct	();
};

}	// sw
