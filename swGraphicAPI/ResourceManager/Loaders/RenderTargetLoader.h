#pragma once
/**
@file RenderTargetLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"

#include "swGraphicAPI/Resources/Textures/RenderTarget.h"
#include "swGraphicAPI/Resources/SwapChain.h"


namespace sw
{


/**@brief Check @ref RenderTargetDescriptor*/
struct RenderTargetLoadInfo : public IAssetLoadInfo, public RenderTargetDescriptor
{
    RTTR_ENABLE( IAssetLoadInfo )
public:

	// ================================ //
	//
	TypeID						GetAssetType		() const
	{
		return TypeID::get< RenderTarget >();
	}

	// ================================ //
	//
	RenderTargetDescriptor		ToDescriptor		() const
	{
		RenderTargetDescriptor descriptor = *this;
		return descriptor;
	}
};

/**@brief Create RenderTarget from existing SwapChain.
@attention Use only in synchronous api.*/
struct RenderTargetFromSwapChain : public IAssetLoadInfo
{
    RTTR_ENABLE( IAssetLoadInfo )
public:

    SwapChain*          Chain;      ///< @todo This can be unsafe is someone releases SwapChain.

public:
    // ================================ //
    //
    TypeID						GetAssetType		() const
    {
        return TypeID::get< RenderTarget >();
    }
};



/**@brief Creates RenderTarget.

Render Target has internal textures which have to be added to ResourceManager.
We need this loader to add them, because asset creators don't have access to ResourceManager.*/
class RenderTargetLoader : public IAssetLoader
{
private:
protected:
public:
	explicit		RenderTargetLoader		() = default;
	virtual			~RenderTargetLoader		() = default;


	virtual bool											CanLoad			( const AssetPath& filePath, TypeID resourceType )															override;
	virtual LoadingResult									Load			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;
	virtual ReturnResult									Prefetch		( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;

};




}	// sw

