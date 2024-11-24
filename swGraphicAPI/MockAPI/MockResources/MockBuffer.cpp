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

// ================================ //

ReturnResult						MockBuffer::UpdateData( BufferRange data, PtrOffset offset )
{
    // Buffer must be updatable.
    if( m_descriptor.Usage == ResourceUsage::Static || m_descriptor.Usage == ResourceUsage::Staging )
        return fmt::format( "Buffer not updatable. Create with ResourceUsage Default or Dynamic. (Current: {})",
                            Convert::ToString( m_descriptor.Usage ) );
    return Success::True;
}

// ================================ //

ReturnResult						MockBuffer::Resize( BufferRange newData )
{
    return Success::True;
}

}	// sw