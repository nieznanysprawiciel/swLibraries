#pragma once
/**
@file VertexShader.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Resources/IShader.h"

#include "swCommonLib/Common/ObjectDeleter.h"
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
	friend ObjectDeleter< VertexShader >;
private:
protected:
	~VertexShader() = default;
public:
	VertexShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

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
	friend ObjectDeleter< PixelShader >;
private:
protected:
	~PixelShader() = default;
public:
	PixelShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

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
	friend ObjectDeleter<GeometryShader>;
private:
protected:
	~GeometryShader() = default;
public:
	GeometryShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

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
	friend ObjectDeleter< ControlShader >;
private:
protected:
	~ControlShader() = default;
public:
	ControlShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

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
	friend ObjectDeleter< EvaluationShader >;
private:
protected:
	~EvaluationShader() = default;
public:
	EvaluationShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};

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
	friend ObjectDeleter<ComputeShader>;
private:
protected:
	~ComputeShader() = default;
public:
	ComputeShader() = default;

	virtual std::string			GetResourceName	() const override { return ""; }
};


}	// sw
