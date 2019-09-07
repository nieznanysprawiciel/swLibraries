/**
@file MaterialAssetInitData.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Assets/MaterialAsset/stdafx.h"


#include "MaterialAssetInitData.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAsset.h"

#include "swGraphicAPI/ResourceManager/nResourceManager.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"



namespace sw
{

// ================================ //
//
ReturnResult                MaterialInitData::AutoCreateBuffer      ( const AssetPath& materialName, nResourceManager* rm )
{
    if( ShadingData.get() != nullptr )
    {
        auto rmAPI = ResourceManagerAPI( rm );

        BufferRange bufferInfo( ShadingData->GetData(), ShadingData->GetSize() );

        auto result = rmAPI.CreateConstantsBuffer( DefaultBufferName( materialName ),
                                                   bufferInfo,
                                                   ShadingData->GetSize(),
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

