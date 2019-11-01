/**
@file swMaterialLoader.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGraphicAPI/Loaders/swMaterialLoader/stdafx.h"


#include "swMaterialLoader.h"

#include "swCommonLib/Common/Converters.h"
#include "swSerialization/Serialization/PropertySerialization/Serialization.h"
#include "swSerialization/Serialization/Deserializer.h"

#include "swGraphicAPI/Assets/MaterialAsset/ShadingModelData.h"
#include "swGraphicAPI/Assets/MaterialAsset/PhongMaterialData.h"

#include "swGraphicAPI/ResourceManager/Loaders/Tools/CanLoad.h"
#include "swGraphicAPI/ResourceManager/PathTranslators/LoadPath.h"
#include "swGraphicAPI/ResourceManager/Exceptions/LoaderException.h"

#include "swCommonLib/Common/fmt.h"


namespace sw
{


// ================================ //
//
SWMaterialLoader::~SWMaterialLoader()
{}

// ================================ //
//
Version             SWMaterialLoader::GetVersion        ()
{
    return Version( 0, 1, 0, 0 );
}

// ================================ //
//
bool                SWMaterialLoader::CanLoad           ( const AssetPath& filePath, TypeID resourceType )
{
    std::string allowedExtensions[] =
    {
        ".swmat",
    };

    TypeID allowedTypes[] =
    {
        TypeID::get< MaterialAsset >(),
        TypeID::get< Resource >()
    };

    return DefaultCanLoad( filePath, resourceType, allowedExtensions, allowedTypes );
}

// ================================ //
//
ReturnResult        SWMaterialLoader::Prefetch          ( const LoadPath& filePath, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
    return ReturnResult();
}


struct STRINGS_0_1_0
{
    static const std::string		FILE_HEADER_STRING;
    static const std::string		VERSION;

    static const std::string		FILE_PATH_STRING;
    static const std::string		SHADER_ENTRY_STRING;

    static const std::string		VERTEX_SHADER_STRING;
    static const std::string		PIXEL_SHADER_STRING;
    static const std::string		GEOMETRY_SHADER_STRING;
    static const std::string		CONTROL_SHADER_STRING;
    static const std::string		EVALUATION_SHADER_STRING;

    static const std::string		TEXTURES_ARRAY_STRING;
    static const std::string		TEXTURE_STRING;

    static const std::string		ADD_BUFFERS_ARRAY_STRING;
    static const std::string		BUFFER_SIZE_STRING;
    static const std::string		SHADING_DATA_STRING;
    static const std::string		SHADING_MODEL_WRAPPER_TYPE_STRING;
};

const std::string		STRINGS_0_1_0::FILE_HEADER_STRING		    = "swMaterial";
const std::string		STRINGS_0_1_0::VERSION                      = "Version";

const std::string		STRINGS_0_1_0::FILE_PATH_STRING			    = "FilePath";
const std::string		STRINGS_0_1_0::SHADER_ENTRY_STRING		    = "ShaderEntry";

const std::string		STRINGS_0_1_0::VERTEX_SHADER_STRING		    = "VertexShader";
const std::string		STRINGS_0_1_0::PIXEL_SHADER_STRING		    = "PixelShader";
const std::string		STRINGS_0_1_0::GEOMETRY_SHADER_STRING	    = "GeometryShader";
const std::string		STRINGS_0_1_0::CONTROL_SHADER_STRING	    = "TesselationControlShader";
const std::string		STRINGS_0_1_0::EVALUATION_SHADER_STRING     = "TesselationEvaluationShader";

const std::string		STRINGS_0_1_0::TEXTURES_ARRAY_STRING	    = "Textures";
const std::string		STRINGS_0_1_0::TEXTURE_STRING               = "Texture";

const std::string		STRINGS_0_1_0::ADD_BUFFERS_ARRAY_STRING                 = "AdditionalBuffers";
const std::string		STRINGS_0_1_0::BUFFER_SIZE_STRING		                = "BufferSize";
const std::string		STRINGS_0_1_0::SHADING_DATA_STRING		                = "ShadingModel";
const std::string		STRINGS_0_1_0::SHADING_MODEL_WRAPPER_TYPE_STRING		= "WrapperType";


const uint32 cMaxMaterialTextures = 5;



// ================================ //
//
LoadingResult       SWMaterialLoader::Load              ( const LoadPath& path, TypeID resourceType, const IAssetLoadInfo* assetDesc, RMLoaderAPI factory )
{
    IDeserializer		deser( std::make_unique< SerializationContext >() );

    if( !deser.LoadFromFile( path.GetFileTranslated().String(), ParsingMode::ParseInsitu ) )
        return LoaderException::Create( "swMaterialLoader", "Deserialization failed: " + deser.GetError() + " ].", path, TypeID::get< MaterialAsset >() );

    if( deser.EnterObject( STRINGS_0_1_0::FILE_HEADER_STRING ) )
    {
        auto loaderVersion = GetVersion();

        auto versionStr = deser.GetAttribute( STRINGS_0_1_0::VERSION, "" );
        auto version = Version::From( versionStr );

        if( !version.IsValid() )
            return LoaderException::Create( "swMaterialLoader", "Can't parse version string.", path, TypeID::get< MaterialAsset >() );

        if( loaderVersion.IsBackwardCompatibileWith( version ) )
        {
            if( version.Get().Major == 0 )
                return LoadMaterial_Version0( path , &deser, LoadingContext( factory ) );
        }
        else
        {
            std::string errorString = "File version " + version.Get().ToString() + " not supported. Maximal version " + loaderVersion.ToString();
            return LoaderException::Create( "swMaterialLoader", errorString, path, TypeID::get< MaterialAsset >() );
        }

        deser.Exit();
    }

    return LoaderException::Create( "swMaterialLoader", "Invalid .swmat file. Header not found.", path, TypeID::get< MaterialAsset >() );
}

// ================================ //
// @todo Maybe we should tell AssetsManager to release resources, if something went wrong.
LoadingResult		                SWMaterialLoader::LoadMaterial_Version0	( const LoadPath& path, IDeserializer* deser, LoadingContext& context )
{
	Nullable< MaterialInitData >	data = Nullable< MaterialInitData >( MaterialInitData () );

	if( deser->EnterObject( TypeID::get< MaterialAsset >().get_name().to_string() ) )
	{
		data = LoadShaders( deser, data, context );
		data = LoadTextures( deser, data, context );
		data = LoadShadingData( deser, data, context );
		data = LoadAdditionalBuffers( deser, data, context );

		deser->Exit();

        // Create MaterialAsset here.
        return CreateMaterial( path, data, context );
	}

	return LoaderException::Create( "swMaterialLoader", "Invalid .swmat file. MaterialAsset entry not found.", path, TypeID::get< MaterialAsset >() );
}

// ================================ //
//
LoadingResult                        SWMaterialLoader::CreateMaterial    ( const LoadPath& path, Nullable< MaterialInitData >& init, LoadingContext& context )
{
    if( !init.IsValid() )
        return LoaderException::Create( "swMaterialLoader", init.GetErrorReason(), path, TypeID::get< MaterialAsset >() );

    init.Get().AutoCreateBuffer( path.GetOriginalPath(), context.Factory );

    auto result = context.Factory.CreateAsset< MaterialAsset >( path.GetOriginalPath(), std::move( init ).Get() );
    if( result.IsValid() )
    {
        context.CollectAsset( result.Get() );
        return { std::move( context.AssetsCollection ), context.Warnings.GetException() };
    }

    return { result.GetError(), std::move( context.Warnings ) };
}

// ================================ //
//
template< typename ShaderType >
inline Nullable< ResourcePtr< ShaderType > >	SWMaterialLoader::LoadShader	( const AssetPath& shaderPath, LoadingContext& context )
{
    if( !shaderPath.GetFile().HasFileName() )
        return Nullable< ResourcePtr< ShaderType > >( fmt::format( "{} path is not set.", Convert::ToString< ShaderType >() ) );

    auto shaderLoadResult = context.Factory.LoadShader< ShaderType >( shaderPath );
    if( !shaderLoadResult.IsValid() )
        return Nullable< ResourcePtr< ShaderType > >( Convert::ToString< ShaderType >() + " file could not be loaded." );

    return shaderLoadResult;
}

// ================================ //
//
Nullable< AssetPath >               SWMaterialLoader::DeserializeShader	    ( IDeserializer* deser, const std::string& shaderNameString )
{
    const char* shaderFile = nullptr;
    const char* shaderEntry = nullptr;

    if( deser->EnterObject( shaderNameString ) )
    {
        shaderEntry = deser->GetAttribute( STRINGS_0_1_0::SHADER_ENTRY_STRING, ( const char* )nullptr );
        shaderFile = deser->GetAttribute( STRINGS_0_1_0::FILE_PATH_STRING, ( const char* )nullptr );

        deser->Exit();

        if( shaderFile && shaderFile )
            return AssetPath( shaderFile, shaderEntry );

        // If there's no entrypoint, default main function will be loaded.
        if( shaderFile )
            return AssetPath( shaderFile, filesystem::Path() );
    }

    return "No shader.";
}

// ================================ //
//
template< typename ShaderType >
ResourcePtr< ShaderType >           SWMaterialLoader::LoadOptionalShader    ( IDeserializer* deser, const std::string& shaderNameString, LoadingContext& context )
{
    auto shaderPath = DeserializeShader( deser, shaderNameString );

    // Note: It's ok, if shader doesn't exist.
    if( shaderPath.IsValid() )
    {
        auto shader = LoadShader< ShaderType >( shaderPath.Get(), context );

        // Here we expect, that shader will be loaded correctly, because we found entry
        // in swmat file. If somethinf was wrong we threat this only as warning.
        if( context.CollectAssetOrWarn( shader ) )
            return std::move( shader ).Get();
    }

    return nullptr;
}

// ================================ //
//
Nullable< MaterialInitData >		SWMaterialLoader::LoadShaders		    ( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context )
{
	ReturnIfInvalid( init );

    auto vertexShaderPath = DeserializeShader( deser, STRINGS_0_1_0::VERTEX_SHADER_STRING );
    if( !vertexShaderPath.IsValid() )
        return "Can't deserialize vertex shader.";

	auto vertexShader = LoadShader< VertexShader >( vertexShaderPath.Get(), context );
    if( vertexShader.IsValid() )
    {
        context.CollectAsset( vertexShader.Get() );
        init.Get().VertexShader = std::move( vertexShader ).Get();
    }
    else
    {
        return vertexShader.GetError();
    }

    auto pixelShaderPath = DeserializeShader( deser, STRINGS_0_1_0::PIXEL_SHADER_STRING );
    if( !pixelShaderPath.IsValid() )
        return "Can't deserialize pixel shader.";

    auto pixelShader = LoadShader< PixelShader >( pixelShaderPath.Get(), context );
    if( pixelShader.IsValid() )
    {
        context.CollectAsset( pixelShader.Get() );
        init.Get().PixelShader = std::move( pixelShader ).Get();
    }
    else
    {
        return pixelShader.GetError();
    }


	// Note: We don't check if shader was created. Nullptrs are acceptable value.
    init.Get().GeometryShader = LoadOptionalShader< GeometryShader >( deser, STRINGS_0_1_0::GEOMETRY_SHADER_STRING, context );
    init.Get().TesselationEvaluationShader = LoadOptionalShader< EvaluationShader >( deser, STRINGS_0_1_0::EVALUATION_SHADER_STRING, context );
    init.Get().TesselationControlShader = LoadOptionalShader< ControlShader >( deser, STRINGS_0_1_0::CONTROL_SHADER_STRING, context );

	return std::move( init );
}

// ================================ //
//
Nullable< MaterialInitData >		SWMaterialLoader::LoadTextures		( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context )
{
	ReturnIfInvalid( init );

	// Textures
	if( deser->EnterArray( STRINGS_0_1_0::TEXTURES_ARRAY_STRING ) )
	{
		if( deser->FirstElement() )
		{
			int texIdx = 0;
			do
			{
				assert( deser->GetName() == STRINGS_0_1_0::TEXTURE_STRING );

				auto assetPath = AssetPath::FromString( deser->GetAttribute( STRINGS_0_1_0::FILE_PATH_STRING, "" ) );

                // AssetPath must have system path part (checked by HasFileName).
                // We don't support generated textures so internal path can't be alone.
				if( assetPath.IsValid() && assetPath.Get().GetFile().HasFileName() )
				{
					auto tex = context.Factory.LoadTexture( assetPath );
                    if( context.CollectAssetOrWarn( tex ) )
					    init.Get().Textures[ texIdx ] = tex.Get();
				}

				texIdx++;
			} while( deser->NextElement() && texIdx < cMaxMaterialTextures );

		}
		deser->Exit();
	}

	return std::move( init );
}

// ================================ //
//
Nullable< MaterialInitData >		SWMaterialLoader::LoadShadingData	( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context )
{
	ReturnIfInvalid( init );
	auto& initData = init.Get();


	// Shading model data
	if( deser->EnterObject( STRINGS_0_1_0::SHADING_DATA_STRING ) )
	{
		uint32		bufferSize = deser->GetAttribute( STRINGS_0_1_0::BUFFER_SIZE_STRING, (uint32)0 );
		const char*	wrapperName = deser->GetAttribute( STRINGS_0_1_0::SHADING_MODEL_WRAPPER_TYPE_STRING, nullptr );

		if( !wrapperName )
			return Nullable< MaterialInitData >( "File doesn't contain WrapperType field." );

		TypeID wrapper = TypeID::get_by_name( wrapperName );
		if( !wrapper.is_valid() )
			return Nullable< MaterialInitData >( "WrapperType is not registered." );

		auto constructor = wrapper.get_constructor();
		if( !constructor.is_valid() )
			return Nullable< MaterialInitData >( "WrapperType constructor is not registered." );

		rttr::variant object = wrapper.create();
		if( !object.is_valid() )
			return Nullable< MaterialInitData >( "WrapperType could not be created." );

		if( !object.can_convert( TypeID::get< ShadingModelBase* >() ) )
			return Nullable< MaterialInitData >( "Can't convert MaterialData to ShadingModelBase*. Make sure, constructor was declared with AsRawPtr policy." );

		initData.ShadingData = UPtr< ShadingModelBase >( object.get_value< ShadingModelBase* >() );

		if( initData.ShadingData->GetSize() != bufferSize )
			return Nullable< MaterialInitData >( "Declared buffer size is other then real buffer size." );


		rttr::variant dataObject = (void*)initData.ShadingData->GetData();
		dataObject.unsafe_convert_void( initData.ShadingData->GetShadingModelPtrType() );


		if( deser->EnterObject( initData.ShadingData->GetShadingModelTypeName() ) )
		{
			SerializationCore::DefaultDeserializeImpl( *deser, dataObject, initData.ShadingData->GetShadingModelType() );

			deser->Exit();
		}
		else
			return Nullable< MaterialInitData >( initData.ShadingData->GetShadingModelTypeName() + " not found in file." );

		deser->Exit();
	}

	return std::move( init );
}

// ================================ //
//
Nullable< MaterialInitData >		SWMaterialLoader::LoadAdditionalBuffers	( IDeserializer* deser, Nullable< MaterialInitData >& init, LoadingContext& context )
{
	ReturnIfInvalid( init );
	auto& initData = init.Get();

	std::vector< ParametricBufferInfo >& addBuffers = init.Get().AdditionalBuffers;

	if( deser->EnterArray( STRINGS_0_1_0::ADD_BUFFERS_ARRAY_STRING ) )
	{
		auto arraySize = deser->GetAttribute( "ArraySize", 0 );
		if( arraySize != 0 )
			addBuffers.reserve( arraySize );

		if( deser->FirstElement() )
		{
			do
			{
                ParametricBufferInfo newBuffer;
				addBuffers.push_back( newBuffer );
				auto newBuffRealPtr = &addBuffers[ addBuffers.size() - 1 ];

				rttr::variant buffVariant = newBuffRealPtr;

                SerializationCore::DefaultDeserializeImpl( *deser, buffVariant, TypeID::get< ParametricBufferInfo >() );

			} while( deser->NextElement() );
		}

		deser->Exit();
	}
	// else there's no buffers probably. It's not an error.

	return std::move( init );
}



//====================================================================================//
//			Material Saver	
//====================================================================================//

// ================================ //
//
void								SWMaterialLoader::SaveMaterial	        ( const filesystem::Path& fileName, MaterialAsset* mat )
{
    ISerializer ser( std::make_unique< SerializationContext >() );

    ser.EnterObject( STRINGS_0_1_0::FILE_HEADER_STRING );

    WriteHeader( ser );

    ser.EnterObject( TypeID::get< MaterialAsset >().get_name().to_string() );

    // Shaders
    WriteShader( ser, mat->GetVertexShader().Ptr(), STRINGS_0_1_0::VERTEX_SHADER_STRING );
    WriteShader( ser, mat->GetPixelShader().Ptr(), STRINGS_0_1_0::PIXEL_SHADER_STRING );
    WriteShader( ser, mat->GetGeometryShader().Ptr(), STRINGS_0_1_0::GEOMETRY_SHADER_STRING );
    WriteShader( ser, mat->GetTessControlShader().Ptr(), STRINGS_0_1_0::CONTROL_SHADER_STRING );
    WriteShader( ser, mat->GetTessEvaluationShader().Ptr(), STRINGS_0_1_0::EVALUATION_SHADER_STRING );

    // Textures
    WriteTextures( ser, mat );

    // Shading model data
    WriteShadingModel( ser, mat->GetDescriptor().ShadingData.get() );

    // Additional buffers
    WriteParametersBuffers( ser, mat );


    ser.Exit();	// type name

    ser.Exit(); // SWMaterial

    ser.SaveFile( fileName.String(), WritingMode::Readable );
}

// ================================ //
//
void                                SWMaterialLoader::WriteHeader       ( ISerializer& ser )
{
    ser.SetAttribute( STRINGS_0_1_0::VERSION, SWMaterialLoader::GetVersion().ToString() );
}

// ================================ //
//
void                                SWMaterialLoader::WriteShader       ( ISerializer& ser, IShader* shader, const std::string& entry )
{
    ser.EnterObject( entry );
    if( shader )
    {
        auto assetPath = shader->GetAssetPath();

        ser.SetAttribute( STRINGS_0_1_0::FILE_PATH_STRING, assetPath.GetFile().String() );
        ser.SetAttribute( STRINGS_0_1_0::SHADER_ENTRY_STRING, assetPath.GetInternalPath().String() );
    }
    ser.Exit();
}

// ================================ //
//
void                                SWMaterialLoader::WriteTextures     ( ISerializer& ser, MaterialAssetPtr mat )
{
    ser.EnterArray( STRINGS_0_1_0::TEXTURES_ARRAY_STRING );

    for( int i = 0; i < cMaxMaterialTextures; ++i )
    {
        auto tex = mat->GetTexture( i );
        WriteTexture( ser, tex );
    }

    ser.Exit();	// Textures
}

// ================================ //
//
void                                SWMaterialLoader::WriteTexture      ( ISerializer& ser, TexturePtr tex )
{
    ser.EnterObject( STRINGS_0_1_0::TEXTURE_STRING );

    if( tex )
        ser.SetAttribute( STRINGS_0_1_0::FILE_PATH_STRING, tex->GetAssetPath().String() );

    ser.Exit();
}

// ================================ //
//
void                                SWMaterialLoader::WriteShadingModel         ( ISerializer& ser, ShadingModelBase* shadingData )
{
    TypeID shadingModelType = shadingData->GetShadingModelType();
    TypeID shadingModelPtrType = shadingData->GetShadingModelPtrType();

    rttr::variant shadingDataPtr( (void* )shadingData->GetData() );
    shadingDataPtr.unsafe_convert_void( shadingModelPtrType );

    ser.EnterObject( STRINGS_0_1_0::SHADING_DATA_STRING );

    ser.SetAttribute( STRINGS_0_1_0::SHADING_MODEL_WRAPPER_TYPE_STRING, shadingData->GetTypeName() );
    ser.SetAttribute( STRINGS_0_1_0::BUFFER_SIZE_STRING, shadingData->GetSize() );

    Serialization().Serialize( ser, shadingDataPtr );

    ser.Exit();		// SHADING_DATA_STRING
}

// ================================ //
//
void                                SWMaterialLoader::WriteParametersBuffers    ( ISerializer& ser, MaterialAssetPtr mat )
{
    Serialization().Serialize( ser, mat->GetDescriptor().ParametricBuffers );
}


}	// sw