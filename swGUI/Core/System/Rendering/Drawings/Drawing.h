#pragma once
/**
@file Drawing.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "IDrawing.h"

#include "swGraphicAPI/Resources/MeshResources.h"
#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"

#include "swCommonLib/Common/Buffers/BufferRange.h"
#include "swCommonLib/Common/Logging/Logger.h"


namespace sw {
namespace gui
{

class Brush;
class Geometry;


namespace impl
{


/**@brief Represents geometry using graphic API structures.

Vertex and Index Buffer contain both fill and border verticies/indicies.
Fill indicies start at offset 0 and end at offset FillEnd.
Border indicies directly follow fill indicies and end at BorderEnd.
Note that verticies layout in Vertex Buffer doesn't matter since indicies reference vertex buffer
from 0 position. That means that fill verticies can be used by border too.*/
struct GeometryRenderingData
{
	BufferPtr                   VertexBuffer;		///< Vertex Buffer containing both fill and border verticies.
    BufferPtr                   IndexBuffer;		///< Index Buffer containing both fill and border indicies.
    BufferPtr                   GeometryConstants;	///< Constant buffer bound to Vertex Shader.
    VertexShaderPtr             VertexShader;		///< Vertex Shader.
    ShaderInputLayoutPtr        Layout;				///< Vertex layout.
	uint32                      FillEnd;			///< End of fill indicies in buffer.
	uint32                      BorderEnd;			///< End of border indicies in buffer.
	PrimitiveTopology           Topology;			///< Geometry topology.
	bool                        ExtendedIB;			///< Index Buffer uses 4-bytes indicies.
};


const u8 NumBrushTextures = 2;


/**@brief Represents brush using graphic API structures.*/
struct BrushRenderingData
{
    PixelShaderPtr      		PixelShader;					///< Pixel Shader.
	BufferPtr       		    BrushConstants;					///< Constant buffer bound to Pixel Shader.
    TexturePtr      	        Texture[ NumBrushTextures ];	///< Optional texture bound to Pixel Shader.
};


}	// impl



/**@brief Simple rendering logic functionalities.

Advanced functionalities will be supported by DrawingGroup.

@ingroup Drawing*/
class Drawing : public IDrawing
{
	RTTR_ENABLE( IDrawing );
	RTTR_REGISTRATION_FRIEND

	FRIEND_CLASS_TESTER( Drawing )
private:

	impl::GeometryRenderingData		m_geometryData;
	impl::BrushRenderingData		m_brushData;
	impl::BrushRenderingData		m_penData;

protected:

	///@name Update rendering data.
	/// Derived classes should use these API functions to set rendering state.
	/// They shouldn't have direct access to rendering structures.
	///@{
	ReturnResult			DefaultRebuildResources		( ResourceManagerAPI rm, ShaderProvider* sp, Brush* brush, Brush* pen, Geometry* geometry );

	ReturnResult            UpdateBrushShader			( ShaderProvider* sp, Brush* brush );
    ReturnResult            UpdateBrushShader			( ShaderProvider* sp, Brush* brush, filesystem::Path shaderTemplate );
    ReturnResult            UpdateBrushTexture			( ResourceManagerAPI rm, Brush* brush );
    ReturnResult            UpdateBrushOpacityMask		( ResourceManagerAPI rm, TexturePtr mask );
    ReturnResult            UpdateBrushConstants		( ResourceManagerAPI rm, Brush* brush );

	ReturnResult            UpdatePenShader				( ShaderProvider* sp, Brush* pen );
    ReturnResult            UpdatePenShader				( ShaderProvider* sp, Brush* pen, filesystem::Path shaderTemplate );
    ReturnResult            UpdatePenTexture			( ResourceManagerAPI rm, Brush* pen );
    ReturnResult            UpdatePenOpacityMask		( ResourceManagerAPI rm, TexturePtr mask );
    ReturnResult            UpdatePenConstants			( ResourceManagerAPI rm, Brush* pen );

	ReturnResult			UpdateVertexShader			( ShaderProvider* sp, Geometry* geometry );
    ReturnResult			UpdateVertexShader			( ShaderProvider* sp, Geometry* geometry, filesystem::Path shaderTemplate );
    ReturnResult			UpdateGeometry				( ResourceManagerAPI rm, Geometry* geometry );
    ReturnResult            UpdateGeometryConstants		( ResourceManagerAPI rm, Geometry* geometry );

	ReturnResult			CreateAndSetLayout			( ResourceManagerAPI rm, ShaderProvider* sp, Geometry* geometry );
    template< typename VertexType >
    ReturnResult			CreateAndSetLayoutForVertexType( ResourceManagerAPI rm, ShaderProvider* sp, Geometry* geometry );
    template < typename VertexStruct >
    sw::Nullable< ShaderInputLayoutPtr >	CreateLayout( ResourceManagerAPI rm, ShaderProvider* sp );
	///@}

	///@name Rendering functions.
	///@{

	/**@brief Updates Brush costants buffer content. Should be called before rendering.*/
	void					UpdateBrushCBContent	( IRenderer* renderer, Brush* brush );

	/**@brief Updates Pen costants buffer content. Should be called before rendering.*/
	void					UpdatePenCBContent		( IRenderer* renderer, Brush* pen );

	/**@brief Updates Geometry costants buffer content. Should be called before rendering.
	This function will update buffer conditionally, if it's necessary. 
	*/
	void					UpdateGeometryCBContent	( IRenderer* renderer, Geometry* geom );

	void					RenderFill				( IRenderer* renderer );
	void					RenderBorder			( IRenderer* renderer );

	///@}

private:

	ReturnResult			UpdateShaderImpl		( ShaderProvider* sp, Brush* brush, impl::BrushRenderingData& brushData, filesystem::Path shaderTemplate );
	ReturnResult			UpdateShaderImpl		( ShaderProvider* sp, Brush* brush, impl::BrushRenderingData& brushData );
	ReturnResult			UpdateTextureImpl		( ResourceManagerAPI rm, Brush* brush, impl::BrushRenderingData& brushData );

	ReturnResult			UpdateCBContentImpl		( IRenderer* renderer, Brush* brush, impl::BrushRenderingData& brushData );
	ReturnResult			UpdateCBContentImpl		( IRenderer* renderer, Buffer* buffer, BufferRange bufferData );

	void					RenderImpl				( IRenderer* renderer, impl::GeometryRenderingData& geom, impl::BrushRenderingData& brush, uint32 start, uint32 end );

public:

	explicit				Drawing	();
	virtual					~Drawing() = default;
};

DEFINE_PTR_TYPE( Drawing )



// ================================ //
//

template < typename VertexType >
inline ReturnResult			Drawing::CreateAndSetLayoutForVertexType( ResourceManagerAPI rm, ShaderProvider* sp,
                                                              Geometry* geometry )
{
    if( !m_geometryData.Layout )
    {
        auto result = CreateLayout< VertexType >( rm, sp );
        ReturnIfInvalid( result );

        m_geometryData.Layout = result.Get();
    }

    return Success::True;
}

// ================================ //
//

template < typename VertexStruct >
sw::Nullable< ShaderInputLayoutPtr >	Drawing::CreateLayout( ResourceManagerAPI rm, ShaderProvider* sp )
{
    auto layout = rm.GetCached< ShaderInputLayout >( GetLayoutName< VertexStruct >() );
    if( !layout )
    {
        return rm.CreateLayout( GetLayoutName< VertexStruct >(), CreateLayoutDescriptor< VertexStruct >() )
                 .MapErr( []( auto e ) { return fmt::format( "Failed to create layout for vertex type: {}. {}", GetLayoutName< VertexStruct >(), e ); } );
    }

    return layout;
}

}  // namespace gui
}	// sw

