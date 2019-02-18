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

	virtual ResourceObject*			Create				( const filesystem::Path& assetName, IAssetCreateInfo&& createInfo )		override;

	virtual ResourceObject*			LoadFromRaw			( const filesystem::Path& assetName, const BufferRaw& rawData )				override;
	virtual BufferRaw				SaveToRaw			( const IAssetCreateInfo& createInfo )										override;
	virtual BufferRaw				SaveToRaw			( ResourcePtr< ResourceObject > resource )									override;

	virtual bool					SupportsResourceToRaw	() override;
	virtual TypeID					GetAssetType			() override;

public:

	inline VertexShader*					CreateVertexShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline PixelShader*						CreatePixelShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline GeometryShader*					CreateGeometryShader		( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline ControlShader*					CreateControlShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline EvaluationShader*				CreateEvaluationShader		( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );
	inline ComputeShader*					CreateComputeShader			( const filesystem::Path& fileName, const std::string& shaderEntry = "main" );

};


}	// sw


#include "ShaderCreator.inl"

