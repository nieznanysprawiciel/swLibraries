/**
@file Drawing.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "Drawing.h"

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
bool			Drawing::DefaultRebuildResources	( ResourceManagerAPI rm, ShaderProvider* sp, Brush* brush, Brush* pen, Geometry* geometry )
{
	bool result = true;

	// Geometry updates
	result = CreateAndSetLayout( rm, sp, geometry ) && result;
	result = UpdateVertexShader( sp, geometry ) && result;
	result = UpdateGeometry( rm, geometry ) && result;
	result = UpdateGeometryConstants( rm, geometry ) && result;

	// Brush updates
	result = UpdateBrushShader( sp, brush ) && result;
	result = UpdateBrushTexture( rm, brush ) && result;
	result = UpdateBrushConstants( rm, brush ) && result;

	// Pen updates
	result = UpdatePenShader( sp, pen ) && result;
	result = UpdatePenTexture( rm, pen ) && result;
	result = UpdatePenConstants( rm, pen ) && result;

	return result;
}

// ================================ //
//
bool			Drawing::UpdateBrushShader			( ShaderProvider* sp, Brush* brush )
{
	return UpdateShaderImpl( sp, brush, m_brushData );
}

// ================================ //
//
bool			Drawing::UpdateBrushTexture			( ResourceManagerAPI rm, Brush* brush )
{
	return UpdateTextureImpl( rm, brush, m_brushData );
}

// ================================ //
//
bool			Drawing::UpdateBrushConstants		( ResourceManagerAPI rm, Brush* brush )
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
		return true;
	}

	return false;
}

// ================================ //
//
bool			Drawing::UpdatePenShader			( ShaderProvider* sp, Brush* pen )
{
	return UpdateShaderImpl( sp, pen, m_penData );
}

// ================================ //
//
bool			Drawing::UpdatePenTexture			( ResourceManagerAPI rm, Brush* pen )
{
	return UpdateTextureImpl( rm, pen, m_penData );
}

// ================================ //
//
bool			Drawing::UpdatePenConstants			( ResourceManagerAPI rm, Brush* pen )
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
		return true;
	}

	return false;
}

// ================================ //
//
bool			Drawing::UpdateVertexShader			( ShaderProvider* sp, Geometry* geometry )
{
	if( geometry->NeedsShaderUpdate() )
	{
		auto brushFunPath = geometry->ShaderFunctionFile();
		m_geometryData.VertexShader = sp->GenerateVS( sp->GetBasicVSTemplate(), brushFunPath );

		geometry->ShaderUpdated();
		return true;
	}

	return false;
}

// ================================ //
//
bool			Drawing::UpdateGeometry				( ResourceManagerAPI rm, Geometry* geometry )
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
		GeometryData data = geometry->Generate();

		// Create new buffers if they didn't existed.
		if( !vertexBuffer || !indexBuffer )
		{
			auto indexSize = data.ExtendedIB ? sizeof( Index32 ) : sizeof( Index16 );
			auto vertexSize = sizeof( VertexShape2D );

			vertexBuffer = rm.CreateVertexBuffer( vbName, data.VertexBuffer, (uint32)vertexSize ).Get();    /// @todo What in case of error?
			indexBuffer = rm.CreateIndexBuffer( ibName, data.IndexBuffer, (uint32)indexSize ).Get();        /// @todo What in case of error?
		}

		m_geometryData.VertexBuffer = vertexBuffer;
		m_geometryData.IndexBuffer = indexBuffer;

		m_geometryData.Topology = data.Topology;
		m_geometryData.FillEnd = data.FillIdxEnd;
		m_geometryData.BorderEnd = data.BorderIdxEnd;
		m_geometryData.ExtendedIB = data.ExtendedIB;

		geometry->GeometryUpdated();
		return true;
	}

	return false;
}

// ================================ //
//
bool			Drawing::UpdateGeometryConstants	( ResourceManagerAPI rm, Geometry* geometry )
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
		return true;
	}

	return false;
}

// ================================ //
//
template< typename VertexStruct >
ShaderInputLayoutPtr		        CreateLayout	( ResourceManagerAPI rm, ShaderProvider* sp )
{
	auto layout = rm.GetCached< ShaderInputLayout >( GetLayoutName< VertexStruct >() );
	if( !layout )
	{
		layout = rm.CreateLayout( GetLayoutName< VertexStruct >(), CreateLayoutDescriptor< VertexStruct >() ).Get();     /// @todo What in case of error?
	}

	return layout;
}


// ================================ //
//
bool			Drawing::CreateAndSetLayout			( ResourceManagerAPI rm, ShaderProvider* sp, Geometry* geometry )
{
	if( !m_geometryData.Layout )
	{
		m_geometryData.Layout = CreateLayout< VertexShape2D >( rm, sp );
		return true;
	}

	return false;
}

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
bool			Drawing::UpdateShaderImpl			( ShaderProvider* sp, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->NeedsShaderUpdate() )
	{
		auto brushFunPath = brush->ShaderFunctionFile();
		brushData.PixelShader = sp->GeneratePS( sp->GetBasicPSTemplate(), brushFunPath );

		brush->ShaderUpdated();
		return true;
	}

	return false;
}

// ================================ //
//
bool			Drawing::UpdateTextureImpl			( ResourceManagerAPI rm, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->NeedsTextureUpdate() )
	{
        AssetPath textureSource = brush->TextureSource();

		// If texture was alredy loaded it will use it.
		///@todo WPF supports not only textures loaded from disk, but also textures from resources
		///referenced by URL. We should change this implementation in future probably.
		brushData.Texture = rm.LoadTexture( textureSource ).Get();      /// @todo What in case of error?

		brush->TextureUpdated();
		return true;
	}

	return false;
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
void			Drawing::UpdateCBContentImpl		( IRenderer* renderer, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->UsesConstantBuffer() )
	{
		if( brushData.BrushConstants.Ptr() != nullptr )
			UpdateCBContentImpl( renderer, brushData.BrushConstants.Ptr(), brush->BufferData() );
		
		/// @todo Error handling
	}
}

// ================================ //
//
void			Drawing::UpdateCBContentImpl		( IRenderer* renderer, Buffer* buffer, BufferRange bufferData )
{
	UpdateBufferCommand cmd;
	cmd.Buffer = buffer;
	cmd.FillData = bufferData.DataPtr;
	cmd.Size = (uint32)bufferData.DataSize;

	renderer->UpdateBuffer( cmd );
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

	helper.SetTexture( setShaderCmd, brush.Texture.Ptr(), 0, (uint8)ShaderType::PixelShader );
	renderer->SetShaderState( setShaderCmd );

	helper.BindBuffer( brush.BrushConstants.Ptr(), 0, (uint8)ShaderType::PixelShader );
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