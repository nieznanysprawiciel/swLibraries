#pragma once
/**
@file ResourceManagerAPI.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/ResourceManager/Loaders/IAssetLoadInfo.h"
#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreateInfo.h"

#include "swGraphicAPI/Resources/MeshResources.h"

#include "swCommonLib/Common/Buffers/BufferRange.h"


namespace sw
{

class nResourceManager;


/**@brief ResourceManager API and additional functions.

This class exposes full ResourceManager API. Some other API classes inherit this, to hide functions,
that shouldn't be used in different contexts like @ref RMLoaderAPI.

Except functionalities of ResourceManager, this class can implement helper functions that
provide less generic and more specific resources managment posibilities.*/
class ResourceManagerAPI
{
protected:

    nResourceManager*       m_resourceManager;		///< Pointer to synchronous resource manager.

public:
    explicit		ResourceManagerAPI		( nResourceManager* resourceManager );
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
    assets referenced by file, but placed in other files.*/
    ResourcePointer								GetCachedGeneric			( const AssetPath& name, TypeID type );

    /**@copydoc nResourceManager::LoadGeneric*/
    sw::Nullable< ResourcePointer >				LoadGeneric					( const AssetPath& assetName, const IAssetLoadInfo* desc, TypeID type );

    /**Typed version of LoadGeneric.
    @copydoc nResourceManager::LoadGeneric*/
    template< typename AssetType >
    sw::Nullable< ResourcePtr< AssetType > >	Load						( const AssetPath& assetName, const IAssetLoadInfo* desc );

    /**@brief Typed version of GetCachedGeneric.
    @copydoc ResourceManagerAPI::GetCachedGeneric*/
    template< typename AssetType >
    ResourcePtr< AssetType >					GetCached					( const AssetPath& name );

    /**@copydoc nResourceManager::CreateGenericAsset*/
    sw::Nullable< ResourcePointer >				CreateGenericAsset			( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo );

    /**Typed version of CreateGenericAsset.
    @copydoc nResourceManager::CreateGenericAsset*/
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

    /// @name Buffers creation functions.
    ///@{
    Nullable< BufferPtr >			            CreateVertexBuffer			( const AssetPath& name, BufferRange buffer, uint32 elementSize );
    Nullable< BufferPtr >			            CreateIndexBuffer			( const AssetPath& name, BufferRange buffer, uint32 elementSize );
    
    /**@brief Creates constants buffer with element of size of whole buffer.
    @note Function doesn't set buffer data type.*/
    Nullable< BufferPtr >			            CreateConstantsBuffer		( const AssetPath& name, BufferRange buffer );
    Nullable< BufferPtr >			            CreateConstantsBuffer		( const AssetPath& name, BufferRange buffer, uint32 elementSize );
    Nullable< BufferPtr >			            CreateConstantsBuffer		( const AssetPath& name, BufferRange buffer, uint32 elementSize, TypeID elementType );

    ///@}

protected:

    template< typename ShaderType >
    Nullable< ResourcePtr< ShaderType > >       LoadShader                  ( const AssetPath& name );
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

    /// @todo It would be nice if Nullable could make this conversion by itself.
    /// It's imposible, because we store ResorucePtr in Nullable and wrappers
    /// types aren't related.
    if( resource.IsValid() )
        return ResourcePtr< AssetType >( static_cast< AssetType* >( resource.Get().Ptr() ) );
    else
        return resource.GetError();
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


//====================================================================================//
//			Private helper functions	
//====================================================================================//

// ================================ //
//
template<typename ShaderType>
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

}	// sw
