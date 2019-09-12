#pragma once
/**
@file swMaterialLoader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Version.h"
#include "swCommonLib/System/Path.h"

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoader.h"

#include "swGraphicAPI/Assets/MaterialAsset/MaterialAssetInitData.h"
#include "swGraphicAPI/Assets/MaterialAsset/MaterialAsset.h"


namespace sw
{


/**@brief Loads .swmat files.
@ingroup Loaders*/
class SWMaterialLoader : public IAssetLoader
{
private:
public:
	explicit						SWMaterialLoader    () = default;
	virtual                         ~SWMaterialLoader   ();

    virtual bool					CanLoad				( const AssetPath& filePath, TypeID resourceType )															override;
    virtual LoadingResult			Load				( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;
    virtual ReturnResult			Prefetch			( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )		override;

public:

    static Version                  GetVersion          ();
    void							SaveMaterial	    ( const filesystem::Path& fileName, MaterialAsset* mat );

private:
	typedef std::pair< const char*, const char* > ShaderLoadInfo;

	Nullable< MaterialInitData >		LoadMaterial_Version1	( IDeserializer* deser );

	Nullable< MaterialInitData >		LoadShaders				( IDeserializer* deser, Nullable< MaterialInitData >& init );
	Nullable< MaterialInitData >		LoadTextures			( IDeserializer* deser, Nullable< MaterialInitData >& init );
	Nullable< MaterialInitData >		LoadShadingData			( IDeserializer* deser, Nullable< MaterialInitData >& init );
	Nullable< MaterialInitData >		LoadAdditionalBuffers	( IDeserializer* deser, Nullable< MaterialInitData >& init );

	ShaderLoadInfo						DeserializeShader		( IDeserializer* deser, const std::string& shaderNameString );

	template< typename ShaderType >
	Nullable< ResourcePtr< ShaderType > >	LoadShader			( IDeserializer* deser, const std::string& shaderNameString );

protected:

    void                                WriteHeader             ( ISerializer& ser );
    void                                WriteShader             ( ISerializer& ser, IShader* shader, const std::string& entry );
    void                                WriteTextures           ( ISerializer& ser, MaterialAssetPtr mat );
    void                                WriteTexture            ( ISerializer& ser, TexturePtr tex );
    void                                WriteShadingModel       ( ISerializer& ser, ShadingModelBase* shadingData );
    void                                WriteParametersBuffers  ( ISerializer& ser, MaterialAssetPtr mat );
};


}	// sw