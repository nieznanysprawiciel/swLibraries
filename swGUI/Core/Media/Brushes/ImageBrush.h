#pragma once
/**
@file ImageBrush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "Brush.h"



namespace sw {
namespace gui
{

/**@brief 
@ingroup Brushes*/
class ImageBrush : public Brush
{
	RTTR_ENABLE( Brush );
	RTTR_REGISTRATION_FRIEND
private:
public:

    enum Stretch
    {
        None = 0,
        Fill = 1,
        Uniform = 2,
        UniformToFill = 3
    };

protected:

    struct Constants
    {
        Rect        TextureRegion;
        Stretch     Stretch;
    };

protected:

    StackBufferA< Constants >		m_constants;
    AssetPath                       m_textureSource;

public:
	explicit		ImageBrush		();
    explicit		ImageBrush		( AssetPath tex );
	virtual         ~ImageBrush	    () = default;

public:

    void			            SetTexture		    ( AssetPath tex );
    const AssetPath&		    GetTexture    	    () const            { return m_textureSource; }

    void                        SetTextureRegion    ( Rect region )     { m_constants.TextureRegion = region; }
    Rect                        GetTextureRegion    () const            { return m_constants.TextureRegion; }

public:

    virtual BufferRange			BufferData			() override;
    virtual filesystem::Path	ShaderFunctionFile	() override;
    virtual AssetPath   		TextureSource		() override;
    virtual AssetPath   		ConstantsName		() override;
};

DEFINE_PTR_TYPE( ImageBrush );

}	// gui
}	// sw


