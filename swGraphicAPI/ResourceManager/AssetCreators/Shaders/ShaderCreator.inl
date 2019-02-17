/**
@file ShaderCreator.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "ShaderCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"

#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"

namespace sw
{

// ================================ //
//
template< typename ShaderObjectType >
inline ResourceObject*		ShaderCreator< ShaderObjectType >::Create			( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	auto & init = static_cast< ShaderInitData&& >( createInfo );

	switch( init.Type )
	{
		case ShaderType::VertexShader:
			return CreateVertexShader( assetName.String(), init.EntryFunction );
		case ShaderType::PixelShader:
			return CreatePixelShader( assetName.String(), init.EntryFunction );
		case ShaderType::GeometryShader:
			return CreateGeometryShader( assetName.String(), init.EntryFunction );
		case ShaderType::ComputeShader:
			return CreateComputeShader( assetName.String(), init.EntryFunction );
		case ShaderType::TesselationControlShader:
			return CreateControlShader( assetName.String(), init.EntryFunction );
		case ShaderType::TesselationEvaluationShader:
			return CreateEvaluationShader( assetName.String(), init.EntryFunction );
		default:
			break;
	}

	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline ResourceObject*		ShaderCreator< ShaderObjectType >::LoadFromRaw		( const filesystem::Path& assetName, const MemoryChunk& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline MemoryChunk			ShaderCreator< ShaderObjectType >::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return MemoryChunk();
}

// ================================ //
//
template< typename ShaderObjectType >
inline MemoryChunk			ShaderCreator< ShaderObjectType >::SaveToRaw		( ResourcePtr< ResourceObject > resource )
{
	assert( !"Buffer is not cacheable" );
	return MemoryChunk();
}

// ================================ //
//
template< typename ShaderObjectType >
inline bool					ShaderCreator< ShaderObjectType >::SupportsResourceToRaw()
{
	return false;
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//


// ================================ //
//
template< typename ShaderObjectType >
inline TypeID				ShaderCreator< ShaderObjectType >::GetAssetType()
{
	return TypeID::get< ShaderObjectType >();
}

// ================================ //
//
template< typename ShaderObjectType >
inline VertexShader*		ShaderCreator< ShaderObjectType >::CreateVertexShader		( const filesystem::Path& fileName, const std::string& shaderEntry )
{
	return ResourcesFactory::CreateVertexShaderFromFile( fileName.WString(), shaderEntry );
}

// ================================ //
//
template< typename ShaderObjectType >
inline PixelShader*			ShaderCreator< ShaderObjectType >::CreatePixelShader		( const filesystem::Path& fileName, const std::string& shaderEntry )
{
	return ResourcesFactory::CreatePixelShaderFromFile( fileName.WString(), shaderEntry );
}

// ================================ //
//
template< typename ShaderObjectType >
inline GeometryShader*		ShaderCreator< ShaderObjectType >::CreateGeometryShader		( const filesystem::Path& fileName, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline ControlShader*		ShaderCreator< ShaderObjectType >::CreateControlShader		( const filesystem::Path& fileName, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline EvaluationShader*	ShaderCreator< ShaderObjectType >::CreateEvaluationShader	( const filesystem::Path & fileName, const std::string & shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline ComputeShader*		ShaderCreator< ShaderObjectType >::CreateComputeShader	( const filesystem::Path & fileName, const std::string & shaderEntry )
{
	return ResourcesFactory::CreateComputeShaderFromFile( fileName.WString(), shaderEntry );
}



}	// sw

