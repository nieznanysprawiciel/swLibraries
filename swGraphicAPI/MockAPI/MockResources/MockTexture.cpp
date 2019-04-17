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
MockTexture::MockTexture( const AssetPath& name, TextureInfo&& texInfo )
	:	Texture( name )
	,	m_descriptor( std::move( texInfo ) )
{
	Construct();
}




// ================================ //
//
MockTexture::~MockTexture()
{}


/**@copydoc Texture::GetDescriptor.*/
const TextureInfo&				MockTexture::GetDescriptor() const
{
	return m_descriptor;
}

/**@brief */
MockTexture*					MockTexture::CreateFromMemory	( const MemoryChunk& texData, TextureInfo&& texInfo )
{
	if( texData.IsNull() )
		return nullptr;

	return new MockTexture( AssetPath( texInfo.FilePath, "" ), std::move( texInfo ) );
}

// ================================ //
//
sw::Nullable< MockTexture* >	MockTexture::CreateFromMemory	( const AssetPath& name, const BufferRaw& texData, TextureInfo&& texInfo )
{
	if( texData.GetData() == nullptr )
		return nullptr;

	return new MockTexture( name, std::move( texInfo ) );
}

/**@brief */
bool							MockTexture::UpdateData			( uint8* dataPtr, uint16 mipLevel, uint16 arrayIdx )
{
	return true;
}

/**@brief */
MemoryChunk						MockTexture::CopyData			() const
{
	MemoryChunk memoryChunk( m_descriptor.MemorySize );
	return std::move( memoryChunk );
}

}	// sw
