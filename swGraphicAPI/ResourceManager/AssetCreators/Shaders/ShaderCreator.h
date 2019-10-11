#pragma once
/**
@file ShaderCreator.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swGraphicAPI/ResourceManager/AssetCreators/IAssetCreator.h"


namespace sw
{


/**@brief Creates shaders objects.

@todo Implement functions to create shader from compiled shaders.
@ingroup AssetsCreators*/
template< typename ShaderObjectType >
class ShaderCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		ShaderCreator		() = default;
	virtual			~ShaderCreator		() = default;


public:

	virtual Nullable< Resource* >	Create				( const AssetPath& assetName, IAssetCreateInfo&& createInfo )				override;

	virtual Nullable< Resource* >	LoadFromRaw			( const AssetPath& assetName, const BufferRaw& rawData )					override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;

public:

	inline Nullable< VertexShader* >				CreateVertexShader			( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry = "main" );
	inline Nullable< PixelShader* >					CreatePixelShader			( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry = "main" );
	inline Nullable< GeometryShader* >				CreateGeometryShader		( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry = "main" );
	inline Nullable< ControlShader*	>				CreateControlShader			( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry = "main" );
	inline Nullable< EvaluationShader* >			CreateEvaluationShader		( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry = "main" );
	inline Nullable< ComputeShader* >				CreateComputeShader			( const AssetPath& fileName, const std::string& code, const std::string& shaderEntry = "main" );

private:

	inline Nullable< Resource* >					CreateShader				( const AssetPath& assetName, ShaderType type, const std::string& code, const std::string& shaderEntry );

};


}	// sw


#include "ShaderCreator.inl"

