#pragma once
/**
@file VertexShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/Shaders/IShader.h"

#include "swCommonLib/System/Path.h"


/**@defgroup Shaders Shaders

Shader creation structures:
- @ref ShaderInitData
- @ref ShaderCodeInitData

@ingroup Resources*/





namespace sw
{


/**@brief Shader type flag.
@ingroup Shaders*/
enum class ShaderType : uint8
{
	VertexShader = 0x01,
	PixelShader = 0x02,
	GeometryShader = 0x04,
	TesselationControlShader = 0x08,
	TesselationEvaluationShader = 0x10,
	ComputeShader = 0x20
};



//----------------------------------------------------------------------------------------------//
//								VertexShader													//
//----------------------------------------------------------------------------------------------//

/** @brief Vertex shader class.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class VertexShader : public IShader
{
	RTTR_ENABLE( IShader );
private:
protected:
	virtual		~VertexShader	() = default;
public:
	explicit	VertexShader	( const AssetPath& assetPath ) : IShader( assetPath ) {}
};

DEFINE_RESOURCE_PTR_TYPE( VertexShader );


//----------------------------------------------------------------------------------------------//
//								PixelShader														//
//----------------------------------------------------------------------------------------------//

/**@brief Pixel shader class.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class PixelShader : public IShader
{
	RTTR_ENABLE( IShader );
private:
protected:
	virtual		~PixelShader	() = default;
public:
	explicit	PixelShader		( const AssetPath& assetPath ) : IShader( assetPath ) {}
};

DEFINE_RESOURCE_PTR_TYPE( PixelShader );


//----------------------------------------------------------------------------------------------//
//								GeometryShader													//
//----------------------------------------------------------------------------------------------//

/**@brief Geometry shader class.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class GeometryShader : public IShader
{
	RTTR_ENABLE( IShader );
private:
protected:
	virtual		~GeometryShader	() = default;
public:
	explicit	GeometryShader	( const AssetPath& assetPath ) : IShader( assetPath ) {}
};

DEFINE_RESOURCE_PTR_TYPE( GeometryShader );


//----------------------------------------------------------------------------------------------//
//								ControlShader													//
//----------------------------------------------------------------------------------------------//

/**@brief Tesselation control shader class.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class ControlShader : public IShader
{
	RTTR_ENABLE( IShader );
private:
protected:
	virtual		~ControlShader	() = default;
public:
	explicit	ControlShader	( const AssetPath& assetPath ) : IShader( assetPath ) {}
};

DEFINE_RESOURCE_PTR_TYPE( ControlShader );


//----------------------------------------------------------------------------------------------//
//								EvaluationShader												//
//----------------------------------------------------------------------------------------------//

/**@brief Tesselation evaluation shader class.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class EvaluationShader : public IShader
{
	RTTR_ENABLE( IShader );
private:
protected:
	virtual		~EvaluationShader	() = default;
public:
	explicit	EvaluationShader	( const AssetPath& assetPath ) : IShader( assetPath ) {}
};

DEFINE_RESOURCE_PTR_TYPE( EvaluationShader );


//----------------------------------------------------------------------------------------------//
//								ComputeShader													//
//----------------------------------------------------------------------------------------------//

/**@brief Compute shader class.
@ingroup Shaders
@ingroup Resources
@ingroup GraphicAPI*/
class ComputeShader : public IShader
{
	RTTR_ENABLE( IShader );
private:
protected:
	virtual		~ComputeShader		() = default;
public:
	explicit	ComputeShader		( const AssetPath& assetPath ) : IShader( assetPath ) {}
};

DEFINE_RESOURCE_PTR_TYPE( ComputeShader );


}	// sw
