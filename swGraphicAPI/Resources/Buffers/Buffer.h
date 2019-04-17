#pragma once
/**
@file Buffer.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/ObjectDeleter.h"

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
	friend ObjectDeleter< Buffer >;
protected:

	unsigned int		m_elementSize;			///< Element size.
	unsigned int		m_elementCount;			///< Number of elements.

	virtual				~Buffer	() = default;
public:

	explicit			Buffer			( const AssetPath& assetPath, unsigned int elementSize, unsigned int elementCount );

	inline unsigned int GetStride		() { return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int	GetElementSize	() { return m_elementSize; }		///<Zwraca rozmiar pojedynczego elementu w buforze.
	inline unsigned int GetElementCount	() { return m_elementCount; }		///<Zwraca liczbê elementów w buforze.
};

DEFINE_RESOURCE_PTR_TYPE( Buffer );


}	// sw

