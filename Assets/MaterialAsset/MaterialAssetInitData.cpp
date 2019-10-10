/**
@file MaterialAssetInitData.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/MaterialAsset/stdafx.h"


#include "MaterialAssetInitData.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAsset.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"



namespace sw
{

// ================================ //
//
ReturnResult                MaterialInitData::AutoCreateBuffer      ( const AssetPath& materialName, RMLoaderAPI& rmAPI )
{
    if( ShadingData.get() != nullptr )
    {
        BufferRange bufferInfo( ShadingData->GetData(), ShadingData->GetSize() );

        auto result = rmAPI.CreateConstantsBuffer( DefaultBufferName( materialName ),
                                                   bufferInfo,
                                                   (uint32)ShadingData->GetSize(),
                                                   ShadingData->GetShadingModelType() );

        if( result.IsValid() )
        {
            this->MaterialBuffer = result.Get();
            return Result::Success;
        }
        else
        {
            return result.GetError();
        }
    }
    else
    {
        return "MaterialInitData.ShadingData was nullptr. Set ShadingModel struct before creating buffer.";
    }
}

// ================================ //
//
AssetPath                   MaterialInitData::DefaultBufferName     ( const AssetPath& materialName ) const
{
    return AssetPath( materialName.GetFile(), materialName.GetInternalPath() / "buffer" );
}


}	// sw

