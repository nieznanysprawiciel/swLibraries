#pragma once
/**
@file RenderTarget.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include "swGraphicAPI/Rendering/GraphicAPIConstants.h"
#include "swGraphicAPI/Resources/ResourcePtr.h"
#include "swGraphicAPI/Resources/Textures/Texture.h"

#include "IRenderTarget.h"

#include <string>


namespace sw
{


/**@defgroup RenderTargets RenderTargets
@ingroup Resources*/




static const std::wstring RENDER_TARGET_COLOR_BUFFER_NAME = L"::color";
static const std::wstring RENDER_TARGET_DEPTH_BUFFER_NAME = L"::depth";
static const std::wstring RENDER_TARGET_STENCIL_BUFFER_NAME = L"::stencil";




/**@brief Structure for creating RenderTarget.
@ingroup RenderTargets*/
struct RenderTargetDescriptor : public IAssetCreateInfo
{
	RTTR_ENABLE( IAssetCreateInfo )
public:
	uint32				Width;						///< Texture width in pixels.
	uint32				Height;						///< Texture height in pixels.
	uint16				ArraySize;					///< Size of array.
	bool				CPURead : 1;				///< Allows to read texture by CPU.
	bool				CPUWrite : 1;				///< Allows to write texture by CPU.
	bool				AllowShareResource : 1;		///< Can share resource between multiple graphic APIs.
	bool				IsCubeMap : 1;				///< True if texture is cube map.
	uint8				NumSamples;					///< Number of samples if RenderTarget format is set to multisampled format.
	uint16				SamplesQuality;				///< Quality of multisampling.
	TextureType			TextureType;				///< Texture type (number of dimensions, multsampling). Only 2-dimensional textures are spoprted now (can be array).
	ResourceFormat		ColorBuffFormat;			///< Format of color buffer
	DepthStencilFormat	DepthStencilFormat;			///< Format depth and stencil buffer.
	ResourceUsage		Usage;						///< Texture usage type. Influences how texture will be placed in GPU memory.

	/**@brief Sets default values for descriptor.*/
	explicit			RenderTargetDescriptor	()
		: Width( 0 )
		, Height( 0 )
		, ArraySize( 1 )
		, CPURead( false )
		, CPUWrite( false )
		, AllowShareResource( false )
		, IsCubeMap( false )
		, Usage( ResourceUsage::Default )
		, TextureType( TextureType::Texture2D )
		, ColorBuffFormat( ResourceFormat::RESOURCE_FORMAT_UNKNOWN )
		, DepthStencilFormat( DepthStencilFormat::DEPTH_STENCIL_FORMAT_D16_UNORM )

	{}

	/**@brief Created TextureInfo  Tworzy strukture TextureInfo wype³nion¹ danymi zgodnymi z deskryptorem RenderTargetu.

	@attention Function doesn't set texture format. We can't deduce format from RenderTargetDescriptor.*/
	TextureInfo			CreateTextureInfo		() const
	{
		TextureInfo texInfo;
		texInfo.Width = Width;
		texInfo.Height = Height;
		texInfo.ArraySize = ArraySize;
		texInfo.CPURead = CPURead;
		texInfo.CPUWrite = CPUWrite;
		texInfo.AllowShareResource = AllowShareResource;
		texInfo.IsCubeMap = IsCubeMap;
		texInfo.TextureType = TextureType;
		texInfo.Usage = Usage;

		return texInfo;
	}


public:
	virtual TypeID		GetAssetType	() const override { return TypeID::get< RenderTarget >(); }
};

/**@brief Class representing render target.
@ingroup RenderTargets
@ingroup Resources
@ingroup GraphicAPI*/
class RenderTarget : public IRenderTarget
{
	RTTR_ENABLE( IRenderTarget );
	RTTR_REGISTRATION_FRIEND;
private:
protected:

	ResourcePtr< Texture >	m_colorBuffer;			///< Can be nullptr.
	ResourcePtr< Texture >	m_depthBuffer;			///< Can be nullptr.
	ResourcePtr< Texture >	m_stencilBuffer;		///< Can be nullptr.

public:

	explicit					RenderTarget	( sw::Texture* colorBuffer, sw::Texture* depthBuffer, sw::Texture* stencilBuffer );
	virtual						~RenderTarget	();

	inline sw::Texture*			GetColorBuffer	() { return m_colorBuffer.Ptr(); }
	inline sw::Texture*			GetDepthBuffer	() { return m_depthBuffer.Ptr(); }
	inline sw::Texture*			GetStencilBuffer() { return m_stencilBuffer.Ptr(); }

	virtual std::string			GetResourceName	() const override;	///<@todo RenderTargety should have their names..
};

DEFINE_RESOURCE_PTR_TYPE( RenderTarget );


}	// sw


