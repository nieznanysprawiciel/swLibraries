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


// ================================ //
//
MockBuffer::MockBuffer( const AssetPath& name, const BufferInfo& descriptor )
	: Buffer( name, descriptor.ElementSize, descriptor.NumElements )
	, m_descriptor( descriptor )
{}

// ================================ //
//
MockBuffer::~MockBuffer()
{}


/**@brief */
sw::Nullable< Buffer* >		MockBuffer::CreateFromMemory	( const AssetPath& name, const uint8* data, const BufferInfo& bufferInfo )
{
	MockBuffer* newBufferObject = new MockBuffer( name, bufferInfo );
	return newBufferObject;
}


/**@brief*/
MemoryChunk							MockBuffer::CopyData			()
{
	MemoryChunk memoryChunk;
	return std::move( memoryChunk );
}

}	// sw