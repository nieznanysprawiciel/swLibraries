#pragma once
/**
@file MockBuffer.h
@author nieznanysprawiciel
@copyright Plik jest częścią silnika graficznego SWEngine.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"

#include "swGraphicAPI/Resources/MeshResources.h"


namespace sw
{

/**@brief 
@ingroup MockAPI*/
class MockBuffer : public Buffer
{
	RTTR_ENABLE( Buffer );
private:

	BufferInfo					m_descriptor;

protected:

	virtual			~MockBuffer		();

public:
	explicit		MockBuffer		( const AssetPath& name, const BufferInfo& descriptor );


	static sw::Nullable< Buffer* >					CreateFromMemory	( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo );

	virtual MemoryChunk								CopyData			() override;
	virtual const BufferInfo&						GetDescriptor		() const { return m_descriptor; }

    virtual ReturnResult							UpdateData			( BufferRange data, PtrOffset offset ) override;
    virtual ReturnResult							Resize				( BufferRange newData ) override;
};

}	// sw
