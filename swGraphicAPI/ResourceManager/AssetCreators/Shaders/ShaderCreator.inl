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




namespace sw
{

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< Resource* >		ShaderCreator< ShaderObjectType >::Create			( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )
{
	if( TypeID::get( createInfo ) == TypeID::get< ShaderInitData >() )
	{
		auto& init = static_cast< ShaderInitData&& >( createInfo );

		std::string code = filesystem::File::Load( assetName );

		switch( init.Type )
		{
			case ShaderType::VertexShader:
				return CreateVertexShader( assetName.String(), code, init.EntryFunction );
			case ShaderType::PixelShader:
				return CreatePixelShader( assetName.String(), code, init.EntryFunction );
			case ShaderType::GeometryShader:
				return CreateGeometryShader( assetName.String(), code, init.EntryFunction );
			case ShaderType::ComputeShader:
				return CreateComputeShader( assetName.String(), code, init.EntryFunction );
			case ShaderType::TesselationControlShader:
				return CreateControlShader( assetName.String(), code, init.EntryFunction );
			case ShaderType::TesselationEvaluationShader:
				return CreateEvaluationShader( assetName.String(), code, init.EntryFunction );
			default:
				break;
		}
	}

	return "[ShaderCreator] IAssetCreateInfo of type [" + TypeID::get( createInfo ).get_name().to_string() + "] not supported yet. This feature will be implemented in future.";
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< Resource* >		ShaderCreator< ShaderObjectType >::LoadFromRaw		( const filesystem::Path& assetName, const BufferRaw& rawData )
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
inline Nullable< VertexShader* >		ShaderCreator< ShaderObjectType >::CreateVertexShader		( const filesystem::Path& fileName, const std::string& code, const std::string& shaderEntry )
{
	return ResourcesFactory::CreateVertexShader( fileName.WString(), code, shaderEntry );
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< PixelShader* >			ShaderCreator< ShaderObjectType >::CreatePixelShader		( const filesystem::Path& fileName, const std::string& code, const std::string& shaderEntry )
{
	return ResourcesFactory::CreatePixelShader( fileName.WString(), code, shaderEntry );
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< GeometryShader* >		ShaderCreator< ShaderObjectType >::CreateGeometryShader		( const filesystem::Path& fileName, const std::string& code, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< ControlShader*	>		ShaderCreator< ShaderObjectType >::CreateControlShader		( const filesystem::Path& fileName, const std::string& code, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< EvaluationShader* >	ShaderCreator< ShaderObjectType >::CreateEvaluationShader	( const filesystem::Path & fileName, const std::string& code, const std::string& shaderEntry )
{
	return nullptr;
}

// ================================ //
//
template< typename ShaderObjectType >
inline Nullable< ComputeShader* >		ShaderCreator< ShaderObjectType >::CreateComputeShader	( const filesystem::Path & fileName, const std::string& code, const std::string & shaderEntry )
{
	return ResourcesFactory::CreateComputeShader( fileName.WString(), code, shaderEntry );
}



}	// sw

