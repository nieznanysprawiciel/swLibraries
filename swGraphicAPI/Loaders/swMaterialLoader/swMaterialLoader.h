#pragma once
/**
@file swMaterialLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Version.h"
#include "swCommonLib/System/Path.h"

#include "swSerialization/Interfaces/Serializer.h"
#include "swSerialization/Interfaces/Deserializer.h"

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"

#include "swGraphicAPI/ResourceManager/Loaders/Tools/LoadingContext.h"

#include "swGraphicAPI/Assets/MaterialAsset/MaterialAssetInitData.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAsset.h"


namespace sw
{


/**@brief Loads .swmat files.

@todo Handle relative paths of textures and shaders. Caller can choose if he wants
to use path aliases or relative paths.

@todo Add tests of ParametricBuffers. Create some utilities to use them in renderers.

@todo More elegant handling of shading models. There's should be no need to register
ShadingModelData wrapper. Material file should contain only shading model structure name
defined by user.

@todo Extract asset saver interface. Saver should support versioning. It should be able to
save older material format version.

@ingroup Loaders*/
class SWMaterialLoader : public IAssetLoader
{
private:
public:
	explicit						SWMaterialLoader    () = default;
	virtual                         ~SWMaterialLoader   ();

    virtual bool					CanLoad				( const AssetPath& filePath, TypeID resourceType )															override;
    virtual LoadingResult			Load				( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI context )		override;
    virtual ReturnResult			Prefetch			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;

public:

    static Version                  GetVersion          ();
    void							SaveMaterial	    ( const filesystem::Path& fileName, MaterialAsset* mat );

private:

    LoadingResult		                LoadMaterial_Version0	( const LoadPath& path, IDeserializer* deser, LoadingContext& context );

    LoadingResult                       CreateMaterial          ( const LoadPath& path, Nullable< MaterialInitData >& init, LoadingContext& context );

	Nullable< MaterialInitData >		LoadShaders				( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context );
	Nullable< MaterialInitData >		LoadTextures			( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context );
	Nullable< MaterialInitData >		LoadShadingData			( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context );
	Nullable< MaterialInitData >		LoadAdditionalBuffers	( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context );

    Nullable< AssetPath >               DeserializeShader		( IDeserializer* deser, const std::string& shaderNameString );

	template< typename ShaderType >
	Nullable< ResourcePtr< ShaderType > >	LoadShader			( const AssetPath& shaderPath, LoadingContext& context );

    template< typename ShaderType >
    ResourcePtr< ShaderType >               LoadOptionalShader  ( IDeserializer* deser, const std::string& shaderNameString, LoadingContext& context );

protected:

    void                                WriteHeader             ( ISerializer& ser );
    void                                WriteShader             ( ISerializer& ser, IShader* shader, const std::string& entry );
    void                                WriteTextures           ( ISerializer& ser, MaterialAssetPtr mat );
    void                                WriteTexture            ( ISerializer& ser, TexturePtr tex );
    void                                WriteShadingModel       ( ISerializer& ser, ShadingModelBase* shadingData );
    void                                WriteParametersBuffers  ( ISerializer& ser, MaterialAssetPtr mat );
};


}	// sw