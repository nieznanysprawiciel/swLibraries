/**
@file MockBuffer.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "MockBuffer.h"
#include "swCommonLib/Common/Converters.h"



RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockBuffer >( "sw::MockBuffer" );
}



namespace sw
{



MockBuffer::MockBuffer( const std::wstring& name, const BufferInfo& descriptor )
	: BufferObject( descriptor.ElementSize, descriptor.NumElements )
	, m_descriptor( descriptor )
{
	m_descriptor.Name = name;
}

MockBuffer::~MockBuffer()
{}


/**@brief */
MockBuffer*		MockBuffer::CreateFromMemory	( const std::wstring& name, const uint8* data, const BufferInfo& bufferInfo )
{
	MockBuffer* newBufferObject = new MockBuffer( name, bufferInfo );
	return newBufferObject;
}


/**@brief*/
MemoryChunk MockBuffer::CopyData()
{
	MemoryChunk memoryChunk;
	return std::move( memoryChunk );
}

}	// sw