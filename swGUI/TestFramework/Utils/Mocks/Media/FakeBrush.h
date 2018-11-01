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
private:
protected:

	std::string			m_shaderFun;

public:

	explicit		FakeBrush		();
	virtual			~FakeBrush		() = default;

public:


	virtual BufferRange				BufferData				() override;
	virtual std::string				ShaderFunctionFile		() override;
	virtual std::wstring			TextureSource			() override;
	virtual std::wstring			ConstantsName			() override;

public:

	using Brush::NeedsShaderUpdate;
	using Brush::NeedsTextureUpdate;
	using Brush::NeedsConstantsUpdate;

public:

	void							SetShaderFunction		( const std::string& shaderFun );
};

DEFINE_PTR_TYPE( FakeBrush )


}	// gui
}	// sw



