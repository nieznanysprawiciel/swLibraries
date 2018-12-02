#include "Drawing.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/Media/Geometry/Geometry.h"

#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"


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

			vertexBuffer = rm->CreateVertexBuffer( name, data.IndexBuffer.GetData(), (uint32)vertexSize, uint32( data.VertexBuffer.GetSize() / indexSize ) );
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



}	// gui
}	// sw