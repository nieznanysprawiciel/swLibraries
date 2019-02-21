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

@todo Implement functions to create shader from cource code in string and from compiled shaders.*/
template< typename ShaderObjectType >
class ShaderCreator : public IAssetCreator
{
private:
protected:
public:
	explicit		ShaderCreator		() = default;
	virtual			~ShaderCreator		() = default;


public:

	virtual Nullable< Resource* >	Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual Nullable< Resource* >	LoadFromRaw			( const filesystem::Path& assetName, const BufferRaw& rawData )				override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< Resource > resource )										override;

	virtual bool					IsCacheable				() const override;
	virtual bool					SupportsResourceToRaw	() const override;
	virtual TypeID					GetAssetType			() const override;

public:

	inline Nullable< VertexShader* >				CreateVertexShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline Nullable< PixelShader* >					CreatePixelShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline Nullable< GeometryShader* >				CreateGeometryShader		( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline Nullable< ControlShader*	>				CreateControlShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline Nullable< EvaluationShader* >			CreateEvaluationShader		( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline Nullable< ComputeShader* >				CreateComputeShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );

};


}	// sw


#include "ShaderCreator.inl"

