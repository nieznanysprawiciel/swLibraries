#pragma once
/**
@file Buffer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/Buffers/IBuffer.h"
#include "swGraphicAPI/Resources/Buffers/BufferInitData.h"



namespace sw
{



/**@brief Object for GPU buffer.

It can be vertex, index or constant buffer.

@ingroup Buffers
@ingroup Resources
@ingroup GraphicAPI*/
class Buffer : public IBuffer
{
	RTTR_ENABLE( IBuffer )
protected:

	uint32				m_elementSize;   ///< Element size.
    uint32				m_elementCount;  ///< Number of elements.

	virtual				~Buffer	() = default;
public:

	explicit			Buffer			( const AssetPath& assetPath, uint32 elementSize, uint32 elementCount );

	inline uint32		GetStride		() const { return m_elementSize; }
    inline uint32       GetElementSize	() const { return m_elementSize; }
    inline uint32       GetElementCount	() const { return m_elementCount; }
    inline Size			GetBytesSize	() const { return m_elementCount * m_elementSize; }
};

DEFINE_RESOURCE_PTR_TYPE( Buffer );


}	// sw

