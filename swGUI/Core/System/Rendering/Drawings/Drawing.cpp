/**
@file Drawing.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "Drawing.h"

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swGraphicAPI/ResourceManager/ResourceManagerAPI.h"
#include "swGUI/Core/System/Rendering/Shading/ShaderProvider.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/Media/Geometry/Geometry.h"
#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"

#include "swGUI/Core/System/Rendering/RenderingHelpers.h"


namespace sw {
namespace gui
{

// ================================ //
//
Drawing::Drawing()
{
	m_geometryData.BorderEnd = 0;
	m_geometryData.ExtendedIB = false;
	m_geometryData.FillEnd = 0;
	m_geometryData.Topology = PrimitiveTopology::Triangles;
}

// ================================ //
//
ReturnResult			Drawing::DefaultRebuildResources	( ResourceManagerAPI rm, ShaderProvider* sp, Brush* brush, Brush* pen, Geometry* geometry )
{
    ErrorsCollector results;

	// Geometry updates
    results.Add( CreateAndSetLayout( rm, sp, geometry ) );
	results.Add( UpdateVertexShader( sp, geometry ) );
	results.Add( UpdateGeometry( rm, geometry ) );
	results.Add( UpdateGeometryConstants( rm, geometry ) );

	// Brush updates
	results.Add( UpdateBrushShader( sp, brush ) );
	results.Add( UpdateBrushTexture( rm, brush ) );
	results.Add( UpdateBrushConstants( rm, brush ) );

	// Pen updates
	results.Add( UpdatePenShader( sp, pen ) );
	results.Add( UpdatePenTexture( rm, pen ) );
	results.Add( UpdatePenConstants( rm, pen ) );

	return results;
}

// ================================ //
//
ReturnResult			Drawing::UpdateBrushShader			( ShaderProvider* sp, Brush* brush )
{
	return UpdateShaderImpl( sp, brush, m_brushData );
}

// ================================ //
//

ReturnResult			Drawing::UpdateBrushShader			( ShaderProvider* sp, Brush* brush, fs::Path shaderTemplate )
{
    return UpdateShaderImpl( sp, brush, m_brushData, shaderTemplate );
}

// ================================ //
//
ReturnResult			Drawing::UpdateBrushTexture			( ResourceManagerAPI rm, Brush* brush )
{
	return UpdateTextureImpl( rm, brush, m_brushData );
}

// ================================ //

ReturnResult			Drawing::UpdateBrushOpacityMask		( ResourceManagerAPI rm, TexturePtr mask )
{
    m_brushData.Texture[ 1 ] = mask;
    return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::UpdateBrushConstants		( ResourceManagerAPI rm, Brush* brush )
{
	if( ( !m_brushData.BrushConstants && brush->UsesConstantBuffer() ) 
		|| brush->NeedsBufferChange() )
	{
		AssetPath name = brush->ConstantsName();

		ResourcePtr< Buffer > constantsBuffer = rm.GetCached< Buffer >( name );
		if( !constantsBuffer )
		{
			auto bufferRange = brush->BufferData();
			constantsBuffer = rm.CreateConstantsBuffer( name, bufferRange ).Get();      /// @todo What in case of error?
		}

		if( brush->NeedsBufferChange() )
			brush->BufferChanged();

		m_brushData.BrushConstants = constantsBuffer;
        return Success::True;
	}

	return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::UpdatePenShader			( ShaderProvider* sp, Brush* pen )
{
	return UpdateShaderImpl( sp, pen, m_penData );
}

// ================================ //
//

ReturnResult			Drawing::UpdatePenShader			( ShaderProvider* sp, Brush* pen, fs::Path shaderTemplate )
{
    return UpdateShaderImpl( sp, pen, m_penData, shaderTemplate );
}

// ================================ //
//
ReturnResult			Drawing::UpdatePenTexture			( ResourceManagerAPI rm, Brush* pen )
{
	return UpdateTextureImpl( rm, pen, m_penData );
}

// ================================ //
//

ReturnResult			Drawing::UpdatePenOpacityMask		( ResourceManagerAPI rm, TexturePtr mask )
{
    m_penData.Texture[ 1 ] = mask;
    return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::UpdatePenConstants			( ResourceManagerAPI rm, Brush* pen )
{
	if( ( !m_penData.BrushConstants && pen->UsesConstantBuffer() )
		|| pen->NeedsBufferChange() )
	{
		AssetPath name = pen->ConstantsName();

		ResourcePtr< Buffer > constantsBuffer = rm.GetCached< Buffer >( name );
		if( !constantsBuffer )
		{
			auto bufferRange = pen->BufferData();
			constantsBuffer = rm.CreateConstantsBuffer( name, bufferRange ).Get();      /// @todo What in case of error?
		}

		if( pen->NeedsBufferChange() )
			pen->BufferChanged();

		m_penData.BrushConstants = constantsBuffer;
        return Success::True;
	}

	return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::UpdateVertexShader			( ShaderProvider* sp, Geometry* geometry )
{
    return UpdateVertexShader( sp, geometry, sp->GetBasicVSTemplate() );
}

// ================================ //
//

ReturnResult			Drawing::UpdateVertexShader			( ShaderProvider* sp, Geometry* geometry, fs::Path shaderTemplate )
{
    if( !m_geometryData.VertexShader || geometry->NeedsShaderUpdate() )
    {
        auto brushFunPath = geometry->ShaderFunctionFile();
        auto result = sp->GenerateVS( shaderTemplate, brushFunPath );
        
		// If shader failed to build, we don't want to repeat attempt in next loop.
		geometry->ShaderUpdated();

		ReturnIfInvalid( result );

        m_geometryData.VertexShader = result.Get(); 
        return Success::True;
    }

    return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::UpdateGeometry				( ResourceManagerAPI rm, Geometry* geometry )
{
	if( geometry->NeedsGeometryUpdate() )
	{
		std::string name = geometry->GeometryName();

        AssetPath vbName = AssetPath( "", name + "/vertex" );
        AssetPath ibName = AssetPath( "", name + "/index" );

		BufferPtr vertexBuffer = rm.GetCached< Buffer >( vbName );
		BufferPtr indexBuffer = rm.GetCached< Buffer >( ibName );

		/// @todo Optimise. We should generate data only if necessary. Introduce Asset for geometric
		/// data that will hold all information needed for rendering.
        auto result = geometry->Generate().MapErr( []( auto e ) { return fmt::format( "[Drawing] Failed to generate Geometry: {}", e ); } );
        ReturnIfInvalid( result );
        GeometryData& data = result.Get();

		// Create new buffers if they didn't exist.
		if( !vertexBuffer )
		{
            auto vertexSize = data.VertexBuffer.GetType().get_sizeof();
            auto result = rm.CreateVertexBuffer( vbName, data.VertexBuffer, (uint32)vertexSize );
            ReturnIfInvalid( result );

            vertexBuffer = result.Get();
		}
		else if( data.VertexBuffer.GetSize() > vertexBuffer->GetBytesSize() )
		{
            ReturnIfInvalid( vertexBuffer->Resize( data.VertexBuffer.AsRange() ) );
		}
		else
		{
			// Buffer is large enough for the new data.
            // Note that we never resize buffer to smaller size. Maybe we should?
            ReturnIfInvalid( vertexBuffer->UpdateData( data.VertexBuffer.AsRange(), 0 ) );
		}
		
		if( !indexBuffer )
		{
			auto indexSize = data.ExtendedIB ? sizeof( Index32 ) : sizeof( Index16 );
            auto result = rm.CreateIndexBuffer( ibName, data.IndexBuffer, (uint32)indexSize );
            ReturnIfInvalid( result );

			indexBuffer = result.Get();
		}
        else if( data.IndexBuffer.GetSize() > indexBuffer->GetBytesSize() )
        {
            ReturnIfInvalid( indexBuffer->Resize( data.IndexBuffer.AsRange() ) );
        }
        else
        {
            // Buffer is large enough for the new data.
            // Note that we never resize buffer to smaller size. Maybe we should?
            ReturnIfInvalid( indexBuffer->UpdateData( data.IndexBuffer.AsRange(), 0 ) );
        }

		m_geometryData.VertexBuffer = vertexBuffer;
		m_geometryData.IndexBuffer = indexBuffer;

		m_geometryData.Topology = data.Topology;
		m_geometryData.FillEnd = data.FillIdxEnd;
		m_geometryData.BorderEnd = data.BorderIdxEnd;
		m_geometryData.ExtendedIB = data.ExtendedIB;

		geometry->GeometryUpdated();
        return Success::True;
	}

	return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::UpdateGeometryConstants	( ResourceManagerAPI rm, Geometry* geometry )
{
	if( !m_geometryData.GeometryConstants && geometry->UsesConstantBuffer() )
	{
		AssetPath name = geometry->ConstantsName();

		BufferPtr constantsBuffer = rm.GetCached< Buffer >( name );
		if( !constantsBuffer )
		{
			auto bufferRange = geometry->BufferData();
			constantsBuffer = rm.CreateConstantsBuffer( name, bufferRange ).Get();      /// @todo What in case of error?
		}

		m_geometryData.GeometryConstants = constantsBuffer;
        return Success::True;
	}

	return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::CreateAndSetLayout			( ResourceManagerAPI rm, ShaderProvider* sp, Geometry* geometry )
{
    return CreateAndSetLayoutForVertexType< VertexShape2D >( rm, sp, geometry );
}

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//

ReturnResult			Drawing::UpdateShaderImpl( ShaderProvider* sp, Brush* brush, impl::BrushRenderingData& brushData, fs::Path shaderTemplate )
{
    if( !brushData.PixelShader || brush->NeedsShaderUpdate() )
    {
        auto brushFunPath = brush->ShaderFunctionFile();
        auto result = sp->GeneratePS( shaderTemplate, brushFunPath );

        // If shader failed to build, we don't want to repeat attempt in next loop.
        brush->ShaderUpdated();

        ReturnIfInvalid( result );

        brushData.PixelShader = result.Get();
        return Success::True;
    }

    return Success::True;
}

// ================================ //
//
ReturnResult			Drawing::UpdateShaderImpl			( ShaderProvider* sp, Brush* brush, impl::BrushRenderingData& brushData )
{
    return UpdateShaderImpl( sp, brush, brushData, sp->GetBasicPSTemplate() );
}

// ================================ //
//
ReturnResult			Drawing::UpdateTextureImpl			( ResourceManagerAPI rm, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->NeedsTextureUpdate() )
	{
        AssetPath textureSource = brush->TextureSource();

		// If texture was alredy loaded it will use it.
		///@todo WPF supports not only textures loaded from disk, but also textures from resources
		///referenced by URL. We should change this implementation in future probably.
        brushData.Texture[0] = rm.LoadTexture( textureSource ).Get();  /// @todo What in case of error?

		brush->TextureUpdated();
        return Success::True;
	}

	return Success::True;
}



//====================================================================================//
//			Rendering	
//====================================================================================//


// ================================ //
//
void			Drawing::UpdateBrushCBContent		( IRenderer* renderer, Brush* brush )
{
	UpdateCBContentImpl( renderer, brush, m_brushData );
}

// ================================ //
//
void			Drawing::UpdatePenCBContent			( IRenderer* renderer, Brush* pen )
{
	UpdateCBContentImpl( renderer, pen, m_penData );
}

// ================================ //
//
void			Drawing::UpdateGeometryCBContent	( IRenderer* renderer, Geometry* geom )
{
	if( geom->UsesConstantBuffer() &&
		geom->UsesSharedBuffer() )
	{
		UpdateCBContentImpl( renderer, m_geometryData.GeometryConstants.Ptr(), geom->BufferData() );
		geom->ConstantsUpdated();
	}
	else if( geom->UsesConstantBuffer() && 
			!geom->UsesSharedBuffer() &&
			 geom->NeedsConstantsUpdate() )
	{
		UpdateCBContentImpl( renderer, m_geometryData.GeometryConstants.Ptr(), geom->BufferData() );
		geom->ConstantsUpdated();
	}
}

// ================================ //
//
void			Drawing::RenderFill					( IRenderer* renderer )
{
	RenderImpl( renderer, m_geometryData, m_brushData, 0, m_geometryData.FillEnd );
}

// ================================ //
//
void			Drawing::RenderBorder				( IRenderer* renderer )
{
	RenderImpl( renderer, m_geometryData, m_penData, m_geometryData.FillEnd, m_geometryData.BorderEnd );
}

// ================================ //
//
ReturnResult	Drawing::UpdateCBContentImpl		( IRenderer* renderer, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->UsesConstantBuffer() )
	{
		if( brushData.BrushConstants.Ptr() != nullptr )
		{
            auto result = UpdateCBContentImpl( renderer, brushData.BrushConstants.Ptr(), brush->BufferData() );
            ReturnIfInvalid( result );
		}
	}
    return Success::True;
}

// ================================ //
//
ReturnResult	 Drawing::UpdateCBContentImpl( IRenderer* renderer, Buffer* buffer, BufferRange bufferData )
{
	UpdateBufferCommand cmd;
	cmd.Buffer = buffer;
	cmd.FillData = bufferData.DataPtr;
	cmd.Size = (uint32)bufferData.DataSize;

	renderer->UpdateBuffer( cmd );
    return Success::True;
}

// ================================ //
//
void			Drawing::RenderImpl					( IRenderer* renderer, impl::GeometryRenderingData& geom, impl::BrushRenderingData& brush, uint32 start, uint32 end )
{
	RenderingHelper helper( renderer );

	SetShaderStateCommand setShaderCmd;
	setShaderCmd.VertexShader = geom.VertexShader.Ptr();
	setShaderCmd.PixelShader = brush.PixelShader.Ptr();
	RenderingHelper::ClearTextureState( setShaderCmd );

	for( auto i = 0; i < std::size( brush.Texture ); i++ )
        helper.SetTexture( setShaderCmd, brush.Texture[ i ].Ptr(), i, (uint8)ShaderType::PixelShader );
	renderer->SetShaderState( setShaderCmd );

	helper.BindBuffer( brush.BrushConstants.Ptr(), 2, (uint8)ShaderType::PixelShader );
	helper.BindBuffer( geom.GeometryConstants.Ptr(), 2, (uint8)ShaderType::VertexShader );
	
	DrawCommand drawCmd;
	drawCmd.VertexBuffer = geom.VertexBuffer.Ptr();
	drawCmd.IndexBufer = geom.IndexBuffer.Ptr();
	drawCmd.ExtendedIndex = geom.ExtendedIB;
	drawCmd.Topology = geom.Topology;
	drawCmd.Layout = geom.Layout.Ptr();
	drawCmd.NumVertices = end - start;
	drawCmd.BufferOffset = start;
	drawCmd.BaseVertex = 0;

	renderer->Draw( drawCmd );
}



}	// gui
}	// sw