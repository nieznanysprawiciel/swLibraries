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

	unsigned int		m_elementSize;			///< Element size.
	unsigned int		m_elementCount;			///< Number of elements.

	virtual				~Buffer	() = default;
public:

	explicit			Buffer			( const AssetPath& assetPath, unsigned int elementSize, unsigned int elementCount );

	inline unsigned int GetStride		() const { return m_elementSize; }
	inline unsigned int	GetElementSize	() const { return m_elementSize; }
	inline unsigned int GetElementCount	() const { return m_elementCount; }
};

DEFINE_RESOURCE_PTR_TYPE( Buffer );


}	// sw

