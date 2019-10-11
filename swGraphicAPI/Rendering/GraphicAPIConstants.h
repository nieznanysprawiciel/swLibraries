#pragma once
/**
@file GraphicAPIConstants.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"


namespace sw
{


/**@brief Blending operation.

@attention Don't change constants order.
@ingroup PipelineState*/
enum class BlendOperation : uint8
{
	Add = 0,
	Subtract = 1,
	ReverseSubtract = 2,
	Min = 3,
	Max = 4
};


/**@brief Blend factor for blending equation.

@attention Don't change constants order.
@ingroup PipelineState*/
enum class BlendFactor : uint8
{
	Zero = 0,
	One = 1,
	SrcColor,
	DstColor,
	SrcAlpha,
	DstAlpha,
	BlendFactor,			///< Custom blend factor. @see BlendingInfo.
	InverseSrcColor,		///< One minus SrcColor
	InverseDstColor,		///< One minus DstColor
	InverseSrcAlpha,		///< One minus SrcAlpha
	InverseDstAlpha,		///< One minus DstAlpha
	InverseBlendFactor		///< One minus custom blend factor. @see BlendingInfo.
};



/**@brief Polygon culling mode.

@attention Don't change constants order.
@ingroup PipelineState*/
enum class CullMode : uint8
{
	Front = 0,
	Back = 1,
	None = 2
};

/**@brief Polygon fill mode.

@attention Don't change constants order.
@ingroup PipelineState*/
enum class FillMode : uint8
{
	Solid = 0,
	Wireframe = 1
};


/**@brief Tells how GPU will access resource.

@attention Don't change constants order.
@see @ref GraphicAPI*/
enum class ResourceUsage : uint8
{
	Default = 0,		///< GPU read and write.
	Dynamic = 1,		///< GPU can read, CPU can write. Use for frequently changing resources.
	Static = 2,			///< Resources is created once and never changes.
	Staging = 3			///< GPU can only copy resource, all access writes are for CPU. @see D3D11_USAGE_STAGING.
};

/**@brief Vertex topology.

@attention Don't change constants order.
@see @ref GraphicAPI*/
enum class PrimitiveTopology : uint8
{
	Points = 0,
	Lines = 1,
	LineStrip = 2,
	Triangles = 3,
	TriangleStrip = 4,
	LinesAdjacency = 5,
	LineStripAdjacency = 6,
	TrianglesAdjacency = 7,
	TriangleStripAdjacency = 8
};

/**@brief Tells how graphic pipeline will use resource.

@attention Engine allows to choose only one of values, but graphic API like DirectX allow to combine these flags.

@attention Don't change constants order.
@see @ref GraphicAPI*/
enum ResourceBinding : uint8
{
	RB_VertexBuffer = 0x0L,
	RB_IndexBuffer = 0x1L,
	RB_ConstantsBuffer = 0x2L,
	RB_ShaderResource = 0x3L,
	RB_StreamOutput = 0x4L,
	RB_RenderTarget = 0x5L,
	RB_DepthStencil = 0x6L,
	RB_UnorderedAccess = 0x7L,
	RB_ResourceDecoder = 0x8L,
	RB_ResourceVideoEncoder = 0x9L

};


/**@brief Defines Texture type.

@attention Don't change constants order.
@see @ref GraphicAPI*/
enum class TextureType : uint8
{
	Unknown = 0,
	Buffer = 1,
	Texture1D = 2,
	TextureArray1D = 3,
	Texture2D = 4,
	TextureArray2D = 5,
	Texture2DMultisample = 6,
	TextureArray2DMultisample = 7,
	Texture3D = 8
};


/**@brief Typy dostêpne dla bufora g³êbokoœci.

@attention Don't change constants order.
@see @ref GraphicAPI*/
enum class DepthStencilFormat : uint8
{
	DEPTH_STENCIL_FORMAT_D32_FLOAT_S8X24_UINT = 0,
	DEPTH_STENCIL_FORMAT_D32_FLOAT = 1,
	DEPTH_STENCIL_FORMAT_D24_UNORM_S8_UINT = 2,
	DEPTH_STENCIL_FORMAT_D16_UNORM = 3
};

/**@brief Specyfikuje format tekstury b¹dŸ innego zasobu.

@attention Don't change constants order.
@see @ref GraphicAPI*/
enum class ResourceFormat : uint8
{
	RESOURCE_FORMAT_UNKNOWN = 0,
	RESOURCE_FORMAT_R32G32B32A32_TYPELESS = 1,
	RESOURCE_FORMAT_R32G32B32A32_FLOAT = 2,
	RESOURCE_FORMAT_R32G32B32A32_UINT = 3,
	RESOURCE_FORMAT_R32G32B32A32_SINT = 4,
	RESOURCE_FORMAT_R32G32B32_TYPELESS = 5,
	RESOURCE_FORMAT_R32G32B32_FLOAT = 6,
	RESOURCE_FORMAT_R32G32B32_UINT = 7,
	RESOURCE_FORMAT_R32G32B32_SINT = 8,
	RESOURCE_FORMAT_R16G16B16A16_TYPELESS = 9,
	RESOURCE_FORMAT_R16G16B16A16_FLOAT = 10,
	RESOURCE_FORMAT_R16G16B16A16_UNORM = 11,
	RESOURCE_FORMAT_R16G16B16A16_UINT = 12,
	RESOURCE_FORMAT_R16G16B16A16_SNORM = 13,
	RESOURCE_FORMAT_R16G16B16A16_SINT = 14,
	RESOURCE_FORMAT_R32G32_TYPELESS = 15,
	RESOURCE_FORMAT_R32G32_FLOAT = 16,
	RESOURCE_FORMAT_R32G32_UINT = 17,
	RESOURCE_FORMAT_R32G32_SINT = 18,
	RESOURCE_FORMAT_R32G8X24_TYPELESS = 19,
	RESOURCE_FORMAT_D32_FLOAT_S8X24_UINT = 20,
	RESOURCE_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
	RESOURCE_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
	RESOURCE_FORMAT_R10G10B10A2_TYPELESS = 23,
	RESOURCE_FORMAT_R10G10B10A2_UNORM = 24,
	RESOURCE_FORMAT_R10G10B10A2_UINT = 25,
	RESOURCE_FORMAT_R11G11B10_FLOAT = 26,
	RESOURCE_FORMAT_R8G8B8A8_TYPELESS = 27,
	RESOURCE_FORMAT_R8G8B8A8_UNORM = 28,
	RESOURCE_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
	RESOURCE_FORMAT_R8G8B8A8_UINT = 30,
	RESOURCE_FORMAT_R8G8B8A8_SNORM = 31,
	RESOURCE_FORMAT_R8G8B8A8_SINT = 32,
	RESOURCE_FORMAT_R16G16_TYPELESS = 33,
	RESOURCE_FORMAT_R16G16_FLOAT = 34,
	RESOURCE_FORMAT_R16G16_UNORM = 35,
	RESOURCE_FORMAT_R16G16_UINT = 36,
	RESOURCE_FORMAT_R16G16_SNORM = 37,
	RESOURCE_FORMAT_R16G16_SINT = 38,
	RESOURCE_FORMAT_R32_TYPELESS = 39,
	RESOURCE_FORMAT_D32_FLOAT = 40,
	RESOURCE_FORMAT_R32_FLOAT = 41,
	RESOURCE_FORMAT_R32_UINT = 42,
	RESOURCE_FORMAT_R32_SINT = 43,
	RESOURCE_FORMAT_R24G8_TYPELESS = 44,
	RESOURCE_FORMAT_D24_UNORM_S8_UINT = 45,
	RESOURCE_FORMAT_R24_UNORM_X8_TYPELESS = 46,
	RESOURCE_FORMAT_X24_TYPELESS_G8_UINT = 47,
	RESOURCE_FORMAT_R8G8_TYPELESS = 48,
	RESOURCE_FORMAT_R8G8_UNORM = 49,
	RESOURCE_FORMAT_R8G8_UINT = 50,
	RESOURCE_FORMAT_R8G8_SNORM = 51,
	RESOURCE_FORMAT_R8G8_SINT = 52,
	RESOURCE_FORMAT_R16_TYPELESS = 53,
	RESOURCE_FORMAT_R16_FLOAT = 54,
	RESOURCE_FORMAT_D16_UNORM = 55,
	RESOURCE_FORMAT_R16_UNORM = 56,
	RESOURCE_FORMAT_R16_UINT = 57,
	RESOURCE_FORMAT_R16_SNORM = 58,
	RESOURCE_FORMAT_R16_SINT = 59,
	RESOURCE_FORMAT_R8_TYPELESS = 60,
	RESOURCE_FORMAT_R8_UNORM = 61,
	RESOURCE_FORMAT_R8_UINT = 62,
	RESOURCE_FORMAT_R8_SNORM = 63,
	RESOURCE_FORMAT_R8_SINT = 64,
	RESOURCE_FORMAT_A8_UNORM = 65,
	RESOURCE_FORMAT_R1_UNORM = 66,
	RESOURCE_FORMAT_R9G9B9E5_SHAREDEXP = 67,
	RESOURCE_FORMAT_R8G8_B8G8_UNORM = 68,
	RESOURCE_FORMAT_G8R8_G8B8_UNORM = 69,
	RESOURCE_FORMAT_BC1_TYPELESS = 70,
	RESOURCE_FORMAT_BC1_UNORM = 71,
	RESOURCE_FORMAT_BC1_UNORM_SRGB = 72,
	RESOURCE_FORMAT_BC2_TYPELESS = 73,
	RESOURCE_FORMAT_BC2_UNORM = 74,
	RESOURCE_FORMAT_BC2_UNORM_SRGB = 75,
	RESOURCE_FORMAT_BC3_TYPELESS = 76,
	RESOURCE_FORMAT_BC3_UNORM = 77,
	RESOURCE_FORMAT_BC3_UNORM_SRGB = 78,
	RESOURCE_FORMAT_BC4_TYPELESS = 79,
	RESOURCE_FORMAT_BC4_UNORM = 80,
	RESOURCE_FORMAT_BC4_SNORM = 81,
	RESOURCE_FORMAT_BC5_TYPELESS = 82,
	RESOURCE_FORMAT_BC5_UNORM = 83,
	RESOURCE_FORMAT_BC5_SNORM = 84,
	RESOURCE_FORMAT_B5G6R5_UNORM = 85,
	RESOURCE_FORMAT_B5G5R5A1_UNORM = 86,
	RESOURCE_FORMAT_B8G8R8A8_UNORM = 87,
	RESOURCE_FORMAT_B8G8R8X8_UNORM = 88,
	RESOURCE_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
	RESOURCE_FORMAT_B8G8R8A8_TYPELESS = 90,
	RESOURCE_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
	RESOURCE_FORMAT_B8G8R8X8_TYPELESS = 92,
	RESOURCE_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
	RESOURCE_FORMAT_BC6H_TYPELESS = 94,
	RESOURCE_FORMAT_BC6H_UF16 = 95,
	RESOURCE_FORMAT_BC6H_SF16 = 96,
	RESOURCE_FORMAT_BC7_TYPELESS = 97,
	RESOURCE_FORMAT_BC7_UNORM = 98,
	RESOURCE_FORMAT_BC7_UNORM_SRGB = 99,
	RESOURCE_FORMAT_AYUV = 100,
	RESOURCE_FORMAT_Y410 = 101,
	RESOURCE_FORMAT_Y416 = 102,
	RESOURCE_FORMAT_NV12 = 103,
	RESOURCE_FORMAT_P010 = 104,
	RESOURCE_FORMAT_P016 = 105,
	RESOURCE_FORMAT_420_OPAQUE = 106,
	RESOURCE_FORMAT_YUY2 = 107,
	RESOURCE_FORMAT_Y210 = 108,
	RESOURCE_FORMAT_Y216 = 109,
	RESOURCE_FORMAT_NV11 = 110,
	RESOURCE_FORMAT_AI44 = 111,
	RESOURCE_FORMAT_IA44 = 112,
	RESOURCE_FORMAT_P8 = 113,
	RESOURCE_FORMAT_A8P8 = 114,
	RESOURCE_FORMAT_B4G4R4A4_UNORM = 115,
	RESOURCE_FORMAT_P208 = 130,
	RESOURCE_FORMAT_V208 = 131,
	RESOURCE_FORMAT_V408 = 132,
};


extern uint32				BitsPerPixel		( ResourceFormat fmt );		///< Liczba bitów na piksel danego formatu. Funkcja wymaga zaimplementrowania przez API graficzne.
extern uint32				BytesPerPixel		( ResourceFormat fmt );		///< Liczba bajtów na piksel danego formatu. Funkcja wymaga zaimplementrowania przez API graficzne.

}	// sw


