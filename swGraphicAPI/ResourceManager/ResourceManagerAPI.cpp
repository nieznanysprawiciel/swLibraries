/**
@file ResourceManagerAPI.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/stdafx.h"

#include "ResourceManagerAPI.h"

#include "swGraphicAPI/ResourceManager/nResourceManager.h"


namespace sw
{

// ================================ //
//
ResourceManagerAPI::ResourceManagerAPI( nResourceManager* resourceManager )
	:	m_resourceManager( resourceManager )
{}

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
    return Load< Texture >( name, nullptr );
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
//			Buffer creation	
//====================================================================================//

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


}	// sw

