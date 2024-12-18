#pragma once
/**
@file DX11Buffer.h
@author nieznanysprawiciel
@copyright Plik jest częścią silnika graficznego SWEngine.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "DX11Initializer/DX11APIObjects.h"




namespace sw
{


/**@brief DirectX11 buffer implementation.
@ingroup DX11API*/
class DX11Buffer : public Buffer, protected DX11APIObjects
{
	RTTR_ENABLE( Buffer );
private:

	ComPtr< ID3D11Buffer >		m_buffer;
	BufferInfo					m_descriptor;

protected:

	~DX11Buffer();

public:

	explicit								DX11Buffer		( const AssetPath& name, const BufferInfo& descriptor, ID3D11Buffer* buff );

	inline ID3D11Buffer*					Get				() { return m_buffer.Get(); }

	static sw::Nullable< Buffer* >			CreateFromMemory( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo );

	virtual MemoryChunk						CopyData		() override;
	virtual const BufferInfo&				GetDescriptor	() const { return m_descriptor; }

    virtual ReturnResult					UpdateData		( BufferRange data, PtrOffset offset ) override;
    virtual ReturnResult					Resize			( BufferRange newData ) override;

protected:
    static sw::Nullable< ID3D11Buffer* >	CreateFromMemoryImpl( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo );
};

}	// sw
