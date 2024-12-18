#pragma once
/**
@file FakeBrush.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGUI/Core/Media/Brushes/Brush.h"


namespace sw {
namespace gui
{


/**@brief Mock brush for tests.*/
class FakeBrush : public Brush
{
public:
    struct Params
    {
        float       FakeLevel;
    };


private:
protected:

	std::string			m_shaderFun;
	std::string		    m_textureFile;
    std::string		    m_cBuffer;
    StackBufferA< Params >      m_constants;

public:

	explicit		FakeBrush		();
	virtual			~FakeBrush		() = default;

public:


	virtual BufferRange				BufferData				() override;
	virtual fs::Path    			ShaderFunctionFile		() override;
	virtual AssetPath			    TextureSource			() override;
	virtual AssetPath			    ConstantsName			() override;

public:

	using Brush::NeedsShaderUpdate;
	using Brush::NeedsTextureUpdate;
	using Brush::NeedsConstantsUpdate;

public:

	void							SetShaderFunction		( const std::string& shaderFun );
	void							SetTextureFile			( const std::string& tex );
	void							ChangeConstsBuffer		( const std::string& newBuffer );
};

DEFINE_PTR_TYPE( FakeBrush )


}	// gui
}	// sw



