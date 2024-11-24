#pragma once
/**
@file ResourceManagerAPI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"

#include "swCommonLib/Common/Buffers/StackBuffer.h"
#include "swCommonLib/Common/Buffers/BufferRange.h"
#include "swCommonLib/Common/Buffers/BufferRaw.h"


namespace sw
{

class ResourceManager;
class PathsManager;


/**@brief ResourceManager API and additional functions.

This class exposes full ResourceManager API. Some other API classes inherit this, to hide functions,
that shouldn't be used in different contexts like @ref RMLoaderAPI.

Except functionalities of ResourceManager, this class can implement helper functions that
provide less generic and more specific resources managment posibilities.*/
class ResourceManagerAPI
{
protected:

    ResourceManager*       m_resourceManager;		///< Pointer to synchronous resource manager.

public:
    explicit		ResourceManagerAPI		( ResourceManager* resourceManager );
    virtual			~ResourceManagerAPI		() = default;

public:

    /**@brief Gets asset that is already loaded or returns nullptr if it isn't.

    Probably there are only rare cases when you want use this function. The main purpose could be checking if assets
    were already loaded by ResourceManager. If Loader can't get asset this way, creates new asset himself.
    I discourage to use GetGeneric for that. Even if asset doesn't exist in ResourceManager, it can be cached
    and ready to load. You should use GetCachedGeneric function in such case.

    The second case is, when Loader wants to load asset referenced by file that he loads. In this case you should
    use LoadGeneric function.*/
    ResourcePointer								GetGeneric					( const AssetPath& name, TypeID type );

    /**@brief Gets asset from ResourceManager or tries to create it from cache.

    Function will return nullptr if it won't find asset and is unable to create it from cache.
    You should always use this function before creating asset in Loader. There're some reasons causing, that
    asset already exist and despite this, Loader was called for the second time:
    - Someone requested asset from file, but didn't set Loader flag to load whole content of file. In this case
    some assets exist in @ref ResourceManager and some not, so second load request must load remaining content.
    - Assets were loaded in the past but they were removed as unnecessary and remained in cache.
    - Editor called LoadFileGeneric. This function always tries to load file even if assets existed and Loaders
    must be prepared for it.

    Don't use LoadGeneric to load assets from file that you are loading. Load Generic should be used to load
    assets referenced by file, but placed in other files.
    
    @todo This function can return nullptr if Asset won't be found. Use Nullable instead.*/
    ResourcePointer								GetCachedGeneric			( const AssetPath& name, TypeID type );

    /**@copydoc ResourceManager::LoadGeneric*/
    sw::Nullable< ResourcePointer >				LoadGeneric					( const AssetPath& assetName, const IAssetLoadInfo* desc, TypeID type );

    /**Typed version of LoadGeneric.
    @copydoc ResourceManager::LoadGeneric*/
    template< typename AssetType >
    sw::Nullable< ResourcePtr< AssetType > >	Load						( const AssetPath& assetName, const IAssetLoadInfo* desc );

    /**@brief Typed version of GetCachedGeneric.
    @copydoc ResourceManagerAPI::GetCachedGeneric*/
    template< typename AssetType >
    ResourcePtr< AssetType >					GetCached					( const AssetPath& name );

    /**@copydoc ResourceManager::CreateGenericAsset*/
    sw::Nullable< ResourcePointer >				CreateGenericAsset			( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo );

    /**Typed version of CreateGenericAsset.
    @copydoc ResourceManager::CreateGenericAsset*/
    template< typename AssetType >
    sw::Nullable< ResourcePtr< AssetType > >	CreateAsset			        ( const AssetPath& name, IAssetCreateInfo&& createInfo );

public:

    Nullable< TexturePtr >                      LoadTexture                 ( const AssetPath& name );

    /// @name Shader loading functions.
    /// Load shader file. Parameter name can contain shader entrypoint as internal path.
    /// If internal path is empty, default entrpoint (main) will be added.
    ///@{
    Nullable< VertexShaderPtr >                 LoadVertexShader            ( const AssetPath& name );
    Nullable< PixelShaderPtr >                  LoadPixelShader             ( const AssetPath& name );
    Nullable< GeometryShaderPtr >               LoadGeometryShader          ( const AssetPath& name );
    Nullable< ControlShaderPtr >                LoadControlShader			( const AssetPath& name );
    Nullable< EvaluationShaderPtr >             LoadEvaluationShader		( const AssetPath& name );
    Nullable< ComputeShaderPtr >                LoadComputeShader		    ( const AssetPath& name );

    ///@}


    /// @name Shader creation
    /// Generate shaders and create them from code. To load shaders from file use
    /// loading functions.
    ///@{
    Nullable< VertexShaderPtr >                 CreateVertexShader          ( const AssetPath& name, std::string code );
    Nullable< PixelShaderPtr >                  CreatePixelShader           ( const AssetPath& name, std::string code );
    Nullable< GeometryShaderPtr >               CreateGeometryShader        ( const AssetPath& name, std::string code );
    Nullable< ControlShaderPtr >                CreateControlShader			( const AssetPath& name, std::string code );
    Nullable< EvaluationShaderPtr >             CreateEvaluationShader		( const AssetPath& name, std::string code );
    Nullable< ComputeShaderPtr >                CreateComputeShader		    ( const AssetPath& name, std::string code );

    Nullable< ShaderInputLayoutPtr >            CreateLayout                ( const AssetPath& name, InputLayoutDescriptor descriptor );

    template< typename ShaderType >
    Nullable< ResourcePtr< ShaderType > >       CreateShader                ( const AssetPath& name, std::string code );
    ///@}

    /// @name Buffers creation functions.
    ///@{
    Nullable< BufferPtr >			            CreateVertexBuffer			( const AssetPath& name, BufferRange buffer, uint32 elementSize );
    Nullable< BufferPtr >			            CreateVertexBuffer			( const AssetPath& name, BufferRange buffer, uint32 elementSize, TypeID elementType );
    Nullable< BufferPtr >			            CreateVertexBuffer			( const AssetPath& name, const BufferRaw& buffer, uint32 elementSize );

    Nullable< BufferPtr >			            CreateIndexBuffer			( const AssetPath& name, BufferRange buffer, uint32 elementSize );
    Nullable< BufferPtr >			            CreateIndexBuffer			( const AssetPath& name, BufferRange buffer, uint32 elementSize, TypeID elementType );
    Nullable< BufferPtr >			            CreateIndexBuffer			( const AssetPath& name, const BufferRaw& buffer, uint32 elementSize );

    template< typename IndexType >
    Nullable< BufferPtr >			            CreateIndexBuffer			( const AssetPath& name, BufferRange buffer );
    
    /**@brief Creates constants buffer with element of size of whole buffer.
    @note Function doesn't set buffer data type.*/
    Nullable< BufferPtr >			            CreateConstantsBuffer		( const AssetPath& name, BufferRange buffer );
    Nullable< BufferPtr >			            CreateConstantsBuffer		( const AssetPath& name, BufferRange buffer, uint32 elementSize );
    Nullable< BufferPtr >			            CreateConstantsBuffer		( const AssetPath& name, BufferRange buffer, uint32 elementSize, TypeID elementType );

    /**@brief Creates buffer from local structure allocated on stack.
    @note Function sets buffer data type. Data type is not necessary to work, but it helps
    for debugging and type retrospection in editor. It is recommended to use typed functions.*/
    template< typename DataStruct >
    Nullable< BufferPtr >			            CreateConstantsBuffer		( const AssetPath& name, const StackBufferA< DataStruct >& buffer );

    ///@}


    /// @name Pipeline State creation
    ///@{
    Nullable< BlendingStatePtr >	            CreateBlendingState			( const AssetPath& name, const BlendingInfo& info );
    Nullable< RasterizerStatePtr >	            CreateRasterizerState		( const AssetPath& name, const RasterizerStateInfo& info );
    Nullable< DepthStencilStatePtr >            CreateDepthStencilState		( const AssetPath& name, const DepthStencilInfo& info );

    ///@}

    PathsManager*                               GetPathsManager             () const;

protected:

    template< typename ShaderType >
    Nullable< ResourcePtr< ShaderType > >       LoadShader                  ( const AssetPath& name );

    template< typename BufferDescType >
    Nullable< BufferDescType >                  CreateBufferDescriptor      ( const AssetPath& name, const uint8* data, uint32 dataSize, uint32 elementSize, TypeID elementType );
};


//====================================================================================//
//			Implementation	
//====================================================================================//




// ================================ //
//
template< typename AssetType >
inline sw::Nullable< ResourcePtr< AssetType > >		ResourceManagerAPI::Load			( const AssetPath& assetName, const IAssetLoadInfo* desc )
{
    auto assetLoadResult = LoadGeneric( assetName, desc, TypeID::get< AssetType >() );

    /// @todo It would be nice if Nullable could make this conversion by itself.
    /// It's imposible, because we store ResorucePtr in Nullable and wrappers
    /// types aren't related.
    if( assetLoadResult.IsValid() )
        return ResourcePtr< AssetType >( static_cast< AssetType* >( assetLoadResult.Get().Ptr() ) );
    else
        return assetLoadResult.GetError();
}

// ================================ //
//
template< typename AssetType >
inline ResourcePtr< AssetType >						ResourceManagerAPI::GetCached		( const AssetPath& name )
{
    auto resource = GetCachedGeneric( name, TypeID::get< AssetType >() );

    // Cast to typed asset.
    return ResourcePtr< AssetType >( static_cast< AssetType* >( resource.Ptr() ) );
}

// ================================ //
//
template< typename AssetType >
inline sw::Nullable< ResourcePtr< AssetType > >     ResourceManagerAPI::CreateAsset     ( const AssetPath& name, IAssetCreateInfo&& createInfo )
{
    auto creationResult = CreateGenericAsset( name, TypeID::get< AssetType >(), std::move( createInfo ) );

    /// @todo It would be nice if Nullable could make this conversion by itself.
    /// It's imposible, because we store ResorucePtr in Nullable and wrappers
    /// types aren't related.
    if( creationResult.IsValid() )
        return ResourcePtr< AssetType >( static_cast< AssetType* >( creationResult.Get().Ptr() ) );
    else
        return creationResult.GetError();
}

// ================================ //
//
template< typename ShaderType >
inline Nullable< ResourcePtr< ShaderType > >        ResourceManagerAPI::CreateShader    ( const AssetPath& name, std::string code )
{
    ShaderCodeInitData init( ShaderInitData::GetFromTypeID( TypeID::get< ShaderType >() ), std::move( code ) );

    // Check if InternalPath contains anything. We should use entrypoint
    // from AssetPath, if it's posible or use default otherwise.
    if( !name.GetInternalPath().HasFileName() )
    {
        init.EntryFunction = name.GetInternalPath().String();
    }

    return CreateAsset< ShaderType >( name, std::move( init ) );
}

// ================================ //
//
template< typename IndexType >
inline Nullable< BufferPtr >                        ResourceManagerAPI::CreateIndexBuffer       ( const AssetPath& name, BufferRange buffer )
{
    return CreateIndexBuffer( name, buffer, sizeof( IndexType ), TypeID::get< IndexType >() );
}

// ================================ //
//
template< typename DataStruct >
inline Nullable< BufferPtr >                        ResourceManagerAPI::CreateConstantsBuffer   ( const AssetPath& name, const StackBufferA< DataStruct >& buffer )
{
    return CreateConstantsBuffer( name, buffer.GetView(), (uint32)buffer.GetSize(), TypeID::get< DataStruct >() );
}

//====================================================================================//
//			Private helper functions	
//====================================================================================//

// ================================ //
//
template< typename ShaderType >
inline Nullable< ResourcePtr< ShaderType > >        ResourceManagerAPI::LoadShader      ( const AssetPath& name )
{
    // Check if InternalPath contains anything. If not we should append
    // default shader entrypoint function.
    if( !name.GetInternalPath().HasFileName() )
    {
        AssetPath path( name.GetFile(), "main" );
        return Load< ShaderType >( path, nullptr );
    }

    return Load< ShaderType >( name, nullptr );
}

// ================================ //
//
template< typename BufferDescType >
inline Nullable< BufferDescType >                   ResourceManagerAPI::CreateBufferDescriptor      ( const AssetPath& name,
                                                                                                      const uint8* data,
                                                                                                      uint32 dataSize,
                                                                                                      uint32 elementSize,
                                                                                                      TypeID elementType )
{
    if( data == nullptr ||
        dataSize == 0 )
        return fmt::format( "Trying to create constant bufffer [{}] using empty BufferRange.", name );

    if( elementSize == 0 )
        return fmt::format( "Trying to create constant bufffer [{}] using [elementSize=0].", name );

    BufferDescType initData;
    initData.Data = data;
    initData.ElementSize = elementSize;
    initData.DataType = elementType;
    initData.NumElements = dataSize / elementSize;

    return initData;
}

}	// sw

