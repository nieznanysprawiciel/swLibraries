/**
@file ResourceManagerAPI.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ResourceManagerAPI.h"

#include "swGraphicAPI/ResourceManager/ResourceManager.h"
#include "swGraphicAPI/ResourceManager/Loaders/TextureLoadInfo.h"


namespace sw
{

// ================================ //
//
ResourceManagerAPI::ResourceManagerAPI( ResourceManager* resourceManager )
	:	m_resourceManager( resourceManager )
{}

// ================================ //
//
ResourcePointer                     ResourceManagerAPI::GetGeneric                  ( const AssetPath& name, TypeID type )
{
    return m_resourceManager->GetGeneric( name, type );
}

// ================================ //
//
ResourcePointer                     ResourceManagerAPI::GetCachedGeneric            ( const AssetPath& name, TypeID type )
{
    /// @todo Call creation from cache, when caching mechanism is ready.
    return m_resourceManager->GetGeneric( name, type );
}

// ================================ //
//
sw::Nullable< ResourcePointer >		ResourceManagerAPI::LoadGeneric				    ( const AssetPath& assetName, const IAssetLoadInfo* desc, TypeID type )
{
    return m_resourceManager->LoadGeneric( assetName, desc, type );
}

// ================================ //
//
Nullable< ResourcePointer >			ResourceManagerAPI::CreateGenericAsset			( const AssetPath& name, TypeID assetType, IAssetCreateInfo&& createInfo )
{
    return m_resourceManager->CreateGenericAsset( name, assetType, std::move( createInfo ) );
}

//====================================================================================//
//			Non generic API	
//====================================================================================//

// ================================ //
//
Nullable< TexturePtr >              ResourceManagerAPI::LoadTexture                 ( const AssetPath& name )
{
    return Load< Texture >( name, &TextureLoadInfo() );
}

//====================================================================================//
//			Shader loading	
//====================================================================================//

// ================================ //
//
Nullable< VertexShaderPtr >         ResourceManagerAPI::LoadVertexShader            ( const AssetPath& name )
{
    return LoadShader< VertexShader >( name );
}

// ================================ //
//
Nullable< PixelShaderPtr >          ResourceManagerAPI::LoadPixelShader             ( const AssetPath& name )
{
    return LoadShader< PixelShader >( name );
}

// ================================ //
//
Nullable< GeometryShaderPtr >       ResourceManagerAPI::LoadGeometryShader          ( const AssetPath& name )
{
    return LoadShader< GeometryShader >( name );
}

// ================================ //
//
Nullable< ControlShaderPtr >        ResourceManagerAPI::LoadControlShader           ( const AssetPath& name )
{
    return LoadShader< ControlShader >( name );
}

// ================================ //
//
Nullable< EvaluationShaderPtr >     ResourceManagerAPI::LoadEvaluationShader        ( const AssetPath& name )
{
    return LoadShader< EvaluationShader >( name );
}

// ================================ //
//
Nullable< ComputeShaderPtr >        ResourceManagerAPI::LoadComputeShader           ( const AssetPath& name )
{
    return LoadShader< ComputeShader >( name );
}

//====================================================================================//
//			Shader creation	
//====================================================================================//

// ================================ //
//
Nullable< VertexShaderPtr >         ResourceManagerAPI::CreateVertexShader          ( const AssetPath& name, std::string code )
{
    return CreateShader< VertexShader >( name, std::move( code ) );
}

// ================================ //
//
Nullable< PixelShaderPtr >          ResourceManagerAPI::CreatePixelShader           ( const AssetPath& name, std::string code )
{
    return CreateShader< PixelShader >( name, std::move( code ) );
}

// ================================ //
//
Nullable< GeometryShaderPtr >       ResourceManagerAPI::CreateGeometryShader        ( const AssetPath& name, std::string code )
{
    return CreateShader< GeometryShader >( name, std::move( code ) );
}

// ================================ //
//
Nullable< ControlShaderPtr >        ResourceManagerAPI::CreateControlShader         ( const AssetPath& name, std::string code )
{
    return CreateShader< ControlShader >( name, std::move( code ) );
}

// ================================ //
//
Nullable< EvaluationShaderPtr >     ResourceManagerAPI::CreateEvaluationShader      ( const AssetPath& name, std::string code )
{
    return CreateShader< EvaluationShader >( name, std::move( code ) );
}

// ================================ //
//
Nullable< ComputeShaderPtr >        ResourceManagerAPI::CreateComputeShader         ( const AssetPath& name, std::string code )
{
    return CreateShader< ComputeShader >( name, std::move( code ) );
}

// ================================ //
//
Nullable< ShaderInputLayoutPtr>     ResourceManagerAPI::CreateLayout                ( const AssetPath& name, InputLayoutDescriptor descriptor )
{
    return CreateAsset< ShaderInputLayout >( name, std::move( descriptor ) );
}

//====================================================================================//
//			Buffer creation	
//====================================================================================//

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateVertexBuffer          ( const AssetPath& name, BufferRange buffer, uint32 elementSize )
{
    return CreateVertexBuffer( name, buffer, elementSize, TypeID::get_by_name( "" ) );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateVertexBuffer          ( const AssetPath& name, BufferRange buffer, uint32 elementSize, TypeID elementType )
{
    VertexBufferInitData initData;
    initData.Data = buffer.DataPtr;
    initData.ElementSize = elementSize;
    initData.DataType = elementType;
    initData.NumElements = (uint32)buffer.DataSize / elementSize;

    return CreateAsset< Buffer >( name, std::move( initData ) );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateVertexBuffer          ( const AssetPath& name, const BufferRaw& buffer, uint32 elementSize )
{
    VertexBufferInitData initData;
    initData.Data = buffer.GetData();
    initData.ElementSize = elementSize;
    initData.DataType = buffer.GetType();
    initData.NumElements = (uint32)buffer.GetSize() / elementSize;

    return CreateAsset< Buffer >( name, std::move( initData ) );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateIndexBuffer           ( const AssetPath& name, BufferRange buffer, uint32 elementSize )
{
    return CreateIndexBuffer( name, buffer, elementSize, TypeID::get_by_name( "" ) );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateIndexBuffer           ( const AssetPath& name, BufferRange buffer, uint32 elementSize, TypeID elementType )
{
    IndexBufferInitData initData;
    initData.Data = buffer.DataPtr;
    initData.ElementSize = elementSize;
    initData.DataType = elementType;
    initData.NumElements = (uint32)buffer.DataSize / elementSize;

    return CreateAsset< Buffer >( name, std::move( initData ) );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateIndexBuffer           ( const AssetPath& name, const BufferRaw& buffer, uint32 elementSize )
{
    IndexBufferInitData initData;
    initData.Data = buffer.GetData();
    initData.ElementSize = elementSize;
    initData.DataType = buffer.GetType();
    initData.NumElements = (uint32)buffer.GetSize() / elementSize;

    return CreateAsset< Buffer >( name, std::move( initData ) );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateConstantsBuffer       ( const AssetPath& name, BufferRange buffer )
{
    return CreateConstantsBuffer( name, buffer, (uint32)buffer.DataSize );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateConstantsBuffer       ( const AssetPath& name, BufferRange buffer, uint32 elementSize )
{
    return CreateConstantsBuffer( name, buffer, elementSize, TypeID::get_by_name( "" ) );
}

// ================================ //
//
Nullable< BufferPtr >               ResourceManagerAPI::CreateConstantsBuffer       ( const AssetPath& name, BufferRange buffer, uint32 elementSize, TypeID elementType )
{
    ConstantBufferInitData initData;
    initData.Data = buffer.DataPtr;
    initData.ElementSize = elementSize;
    initData.DataType = elementType;
    initData.NumElements = (uint32 )buffer.DataSize / elementSize;

    return CreateAsset< Buffer >( name, std::move( initData ) );
}


//====================================================================================//
//			Pipeline states creation	
//====================================================================================//

// ================================ //
//
Nullable< BlendingStatePtr >        ResourceManagerAPI::CreateBlendingState         ( const AssetPath& name, const BlendingInfo& info )
{
    return CreateAsset< BlendingState >( name, BlendingInfo( info ) );
}

// ================================ //
//
Nullable< RasterizerStatePtr >      ResourceManagerAPI::CreateRasterizerState       ( const AssetPath& name, const RasterizerStateInfo& info )
{
    return CreateAsset< RasterizerState >( name, RasterizerStateInfo( info ) );
}

// ================================ //
//
Nullable< DepthStencilStatePtr >    ResourceManagerAPI::CreateDepthStencilState     ( const AssetPath& name, const DepthStencilInfo& info )
{
    return CreateAsset< DepthStencilState >( name, DepthStencilInfo( info ) );
}


}	// sw

