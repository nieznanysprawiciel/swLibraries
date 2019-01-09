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
	m_geometryData.Topology = PrimitiveTopology::PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

// ================================ //
//
bool			Drawing::DefaultRebuildResources	( ResourceManager* rm, ShaderProvider* sp, Brush* brush, Brush* pen, Geometry* geometry )
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
bool			Drawing::UpdateBrushTexture			( ResourceManager* rm, Brush* brush )
{
	return UpdateTextureImpl( rm, brush, m_brushData );
}

// ================================ //
//
bool			Drawing::UpdateBrushConstants		( ResourceManager* rm, Brush* brush )
{
	if( !m_brushData.BrushConstants && brush->UsesConstantBuffer() )
	{
		std::wstring name = brush->ConstantsName();

		ResourcePtr< BufferObject > constantsBuffer = rm->GetConstantBuffer( name );
		if( !constantsBuffer )
		{
			auto bufferRange = brush->BufferData();
			constantsBuffer = rm->CreateConstantsBuffer( name, bufferRange.DataPtr, (uint32)bufferRange.DataSize );
		}

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
bool			Drawing::UpdatePenTexture			( ResourceManager* rm, Brush* pen )
{
	return UpdateTextureImpl( rm, pen, m_penData );
}

// ================================ //
//
bool			Drawing::UpdatePenConstants			( ResourceManager* rm, Brush* pen )
{
	if( !m_penData.BrushConstants && pen->UsesConstantBuffer() )
	{
		std::wstring name = pen->ConstantsName();

		ResourcePtr< BufferObject > constantsBuffer = rm->GetConstantBuffer( name );
		if( !constantsBuffer )
		{
			auto bufferRange = pen->BufferData();
			constantsBuffer = rm->CreateConstantsBuffer( name, bufferRange.DataPtr, (uint32)bufferRange.DataSize );
		}

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
bool			Drawing::UpdateGeometry				( ResourceManager* rm, Geometry* geometry )
{
	if( geometry->NeedsGeometryUpdate() )
	{
		std::wstring name = geometry->GeometryName();

		ResourcePtr< BufferObject > vertexBuffer = rm->GetVertexBuffer( name );
		ResourcePtr< BufferObject > indexBuffer = rm->GetIndexBuffer( name );

		/// @todo Optimise. We should generate data only if necessary. Introduce Asset for geometric
		/// data that will hold all information needed for rendering.
		GeometryData data = geometry->Generate();

		// Create new buffers if they didn't existed.
		if( !vertexBuffer || !indexBuffer )
		{
			auto indexSize = data.ExtendedIB ? sizeof( Index32 ) : sizeof( Index16 );
			auto vertexSize = sizeof( VertexShape2D );

			vertexBuffer = rm->CreateVertexBuffer( name, data.VertexBuffer.GetData(), (uint32)vertexSize, uint32( data.VertexBuffer.GetSize() / indexSize ) );
			indexBuffer = rm->CreateIndexBuffer( name, data.IndexBuffer.GetData(), (uint32)indexSize, uint32( data.IndexBuffer.GetSize() / indexSize ) );
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
bool			Drawing::UpdateGeometryConstants	( ResourceManager* rm, Geometry* geometry )
{
	if( !m_geometryData.GeometryConstants && geometry->UsesConstantBuffer() )
	{
		std::wstring name = geometry->ConstantsName();

		ResourcePtr< BufferObject > constantsBuffer = rm->GetConstantBuffer( name );
		if( !constantsBuffer )
		{
			auto bufferRange = geometry->BufferData();
			constantsBuffer = rm->CreateConstantsBuffer( name, bufferRange.DataPtr, (uint32)bufferRange.DataSize );
		}

		m_geometryData.GeometryConstants = constantsBuffer;
		return true;
	}

	return false;
}

// ================================ //
//
template< typename VertexStruct >
ResourcePtr< ShaderInputLayout >		CreateLayout	( ResourceManager* rm, ShaderProvider* sp )
{
	auto layout = rm->GetLayout( GetLayoutName< VertexStruct >() );
	if( !layout )
	{
		auto pm = sp->GetPathsManager();
		auto exampleShaderPath = pm->Translate( GetLayoutExampleShader< VertexStruct >() );

		rm->LoadVertexShader( exampleShaderPath.WString(), "main", &layout, CreateLayoutDescriptor< VertexStruct >().get() );

		if( !layout )
		{
			// We should handle this error better.
			throw std::exception( "Drawing::CreateLayout - Creating layout failed. Chack if example shader exists." );
			return nullptr;
		}
	}

	return layout;
}


// ================================ //
//
bool			Drawing::CreateAndSetLayout			( ResourceManager* rm, ShaderProvider* sp, Geometry* geometry )
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
bool			Drawing::UpdateTextureImpl			( ResourceManager* rm, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->NeedsTextureUpdate() )
	{
		std::wstring textureSource = brush->TextureSource();

		// If texture was alredy loaded it will use it.
		///@todo WPF supports not only textures loaded from disk, but also textures from resources
		///referenced by URL. We should change this implementation in future probably.
		brushData.Texture = rm->LoadTexture( textureSource );

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
	RenderImpl( renderer, m_geometryData, m_brushData, m_geometryData.FillEnd, m_geometryData.BorderEnd );
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
void			Drawing::UpdateCBContentImpl		( IRenderer* renderer, BufferObject* buffer, BufferRange bufferData )
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
	helper.BindBuffer( geom.GeometryConstants.Ptr(), 1, (uint8)ShaderType::VertexShader );
	
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