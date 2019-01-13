/**
@file MockTexture.cpp
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "MockTexture.h"





RTTR_REGISTRATION
{
	rttr::registration::class_< sw::MockTexture >( "sw::MockTexture" );
}


namespace sw
{


// ================================ //
//
void MockTexture::Construct()
{}



/**@brief */
MockTexture::MockTexture( TextureInfo&& texInfo )
	: m_descriptor( std::move( texInfo ) )
{
	Construct();
}




// ================================ //
//
MockTexture::~MockTexture()
{}


/**@copydoc TextureObject::GetDescriptor.*/
const TextureInfo&			MockTexture::GetDescriptor() const
{
	return m_descriptor;
}

/**@copydoc TextureObject::GetFilePath.*/
const filesystem::Path&		MockTexture::GetFilePath() const
{
	return m_descriptor.FilePath;
}


/**@brief */
MockTexture*	MockTexture::CreateFromMemory( const MemoryChunk& texData, TextureInfo&& texInfo )
{
	if( texData.IsNull() )
		return nullptr;

	return new MockTexture( std::move( texInfo ) );
}

/**@brief */
bool			MockTexture::UpdateData			( uint8* dataPtr, uint16 mipLevel, uint16 arrayIdx )
{
	return true;
}

/**@brief */
MemoryChunk					MockTexture::CopyData() const
{
	MemoryChunk memoryChunk( m_descriptor.MemorySize );
	return std::move( memoryChunk );
}

}	// sw
