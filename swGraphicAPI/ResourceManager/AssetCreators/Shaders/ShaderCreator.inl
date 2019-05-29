/**
@file ShaderCreator.inl
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "ShaderCreator.h"
#include "swGraphicAPI/Resources/MeshResources.h"

#include "swGraphicAPI/Resources/Shaders/ShaderInitData.h"

#include "swCommonLib/Common/Buffers/BufferTyped.h"
#include "swCommonLib/System/File.h"
#include "swCommonLib/Common/Exceptions/Common/InvalidCodeLogicException.h"




namespace sw
{


// ================================ //
//
template< typename ShaderObjectType >
Nullable< Resource* >				ShaderCreator< ShaderObjectType >::CreateShader		( const AssetPath& assetName, ShaderType type, const std::string& code, const std::string& shaderEntry )
{
	switch( type )
	{
	case ShaderType::VertexShader:
		return CreateVertexShader( assetName, code, shaderEntry );
	case ShaderType::PixelShader:
		return CreatePixelShader( assetName, code, shaderEntry );
	case ShaderType::GeometryShader:
		return CreateGeometryShader( assetName, code, shaderEntry );
	case ShaderType::ComputeShader:
		return CreateComputeShader( assetName, code, shaderEntry );
	case ShaderType::TesselationControlShader:
		return CreateControlShader( assetName, code, shaderEntry );
	case ShaderType::TesselationEvaluationShader:
		return CreateEvaluationShader( assetName, code, shaderEntry );
	default:
		return InvalidCodeLogicException::Create( "[ShaderCreator] Unknown shader type", __FILE__, __LINE__ );
	}
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< Resource* >		ShaderCreator< ShaderObjectType >::Create			( const AssetPath& assetName, IAssetCreateInfo&& createInfo )
{
	if( TypeID::get( createInfo ) == TypeID::get< ShaderInitData >() )
	{
		auto& init = static_cast< ShaderInitData&& >( createInfo );
		std::string code = filesystem::File::Load( assetName.GetFile() );
		
		return CreateShader( assetName, init.Type, code, init.EntryFunction );
	}
	else if( TypeID::get( createInfo ) == TypeID::get< ShaderCodeInitData >() )
	{
		auto& init = static_cast< ShaderCodeInitData&& >( createInfo );

		return CreateShader( assetName, init.Type, init.SourceCode, init.EntryFunction );
	}
	else
	{
		return "[ShaderCreator] IAssetCreateInfo of type [" + TypeID::get( createInfo ).get_name().to_string() + "] not supported yet.";
	}
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< Resource* >		ShaderCreator< ShaderObjectType >::LoadFromRaw		( const AssetPath& assetName, const BufferRaw& rawData )
{
	assert( !"Buffer is not cacheable" );
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline BufferRaw					ShaderCreator< ShaderObjectType >::SaveToRaw		( const IAssetCreateInfo& createInfo )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
template< typename ShaderObjectType >
inline BufferRaw					ShaderCreator< ShaderObjectType >::SaveToRaw		( ResourcePtr< Resource > resource )
{
	assert( !"Buffer is not cacheable" );
	return BufferTyped< uint8 >::CreateEmpty();
}

// ================================ //
//
template< typename ShaderObjectType >
inline bool							ShaderCreator< ShaderObjectType >::IsCacheable		() const
{
	return false;
}

// ================================ //
//
template< typename ShaderObjectType >
inline bool							ShaderCreator< ShaderObjectType >::SupportsResourceToRaw() const
{
	return false;
}

//====================================================================================//
//			Non generic functions.	
//====================================================================================//


// ================================ //
//
template< typename ShaderObjectType >
inline TypeID							ShaderCreator< ShaderObjectType >::GetAssetType				() const
{
	return TypeID::get< ShaderObjectType >();
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< VertexShader* >		ShaderCreator< ShaderObjectType >::CreateVertexShader		( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry )
{
	return ResourcesFactory::CreateVertexShader( fileName, code, shaderEntry );
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< PixelShader* >			ShaderCreator< ShaderObjectType >::CreatePixelShader		( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry )
{
	return ResourcesFactory::CreatePixelShader( fileName, code, shaderEntry );
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< GeometryShader* >		ShaderCreator< ShaderObjectType >::CreateGeometryShader		( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< ControlShader*	>		ShaderCreator< ShaderObjectType >::CreateControlShader		( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< EvaluationShader* >	ShaderCreator< ShaderObjectType >::CreateEvaluationShader	( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< ComputeShader* >		ShaderCreator< ShaderObjectType >::CreateComputeShader		( const AssetPath& fileName, const std::string& code, const std::string & shaderEntry )
{
	return ResourcesFactory::CreateComputeShader( fileName, code, shaderEntry );
}



}	// sw

