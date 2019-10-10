#pragma once
/**
@file RenderTargetLoadInfo.h
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

    SwapChain* Chain;      ///< @todo This can be unsafe is someone releases SwapChain.

public:
    // ================================ //
    //
    TypeID						GetAssetType		() const
    {
        return TypeID::get< RenderTarget >();
    }
};


}	// sw


