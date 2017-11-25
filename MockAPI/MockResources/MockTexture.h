#pragma once


#include "swGraphicAPI/Resources/MeshResources.h"



namespace sw
{



/**@brief
@ingroup MockAPI*/
class MockTexture : public TextureObject
{
	RTTR_ENABLE( TextureObject )
private:
	TextureInfo								m_descriptor;
protected:
	~MockTexture();
public:
	explicit								MockTexture				( TextureInfo&& texInfo );

	virtual MemoryChunk						CopyData				() const override;
	virtual const TextureInfo&				GetDescriptor			() const override;

	virtual const filesystem::Path&			GetFilePath				() const override;

	static MockTexture*						CreateFromMemory		( const MemoryChunk& texData, TextureInfo&& texInfo );



private:
	void		Construct	();
};

}	// sw
