/**
@file FreeTypeLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/TextAsset/stdafx.h"

#include "FontLoader.h"

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"
#include <swGraphicAPI/ResourceManager/Loaders/Tools/CanLoad.h>

#include "swGraphicAPI/Assets/TextAsset/Loader/FreeType.h"


namespace sw
{




FreeTypeLoader::~FreeTypeLoader()
{
}

bool                FreeTypeLoader::CanLoad( const AssetPath& filePath, TypeID resourceType )
{
    std::string allowedExtensions[] =
    {
        ".ttf",
    };

    TypeID allowedTypes[] =
    {
        TypeID::get< FontAsset >(),
        TypeID::get< Resource >()
    };

    return DefaultCanLoad( filePath, resourceType, allowedExtensions, allowedTypes );
}

ReturnResult        FreeTypeLoader::Prefetch( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
    return ReturnResult( fmt::format( "Prefetch operation not supported" ) );
}

LoadingResult       FreeTypeLoader::Load( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI context )
{
    auto freeType = FreeTypeLibrary::Create();

    return LoadingResult();
}


Nullable<FreeTypeLibrary>   FreeTypeLibrary::Create()
{
    FT_Library library;
    auto error = FT_Init_FreeType( &library );
    if( error )
        return Nullable< FreeTypeLibrary >::FromError( fmt::format( "Failed to initialize FreeType library." ) );
    return FreeTypeLibrary( library );
}

ReturnResult                FreeTypeLibrary::CreateFace( const LoadPath& filePath )
{
    FT_Error error = FT_New_Face( this->Library, filePath.GetFile().String().c_str(), 0, &this->Face);
    if( error != FT_Err_Ok )
    {
        return ReturnResult( fmt::format( "Failed to create face from font file: {}, error: {}",
            filePath.GetFile().String(), FT_Error_String( error ) ) );
    }

    return Success::True;
    
}

FreeTypeLibrary::~FreeTypeLibrary()
{
    FT_Done_FreeType( this->Library );
}

}
