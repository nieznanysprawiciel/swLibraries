#include "Drawing.h"

#include "swGUI/Core/Media/Brushes/Brush.h"
#include "swGUI/Core/Media/Geometry/Geometry.h"

#include "swGUI/Core/Media/Geometry/Layouts/VertexShape2D.h"


namespace sw {
namespace gui
{


// ================================ //
//
bool			Drawing::UpdateBrushShader			( ResourceManager* rm, Brush* brush )
{
	return UpdateShaderImpl( rm, brush, m_brushData );
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
	return false;
}

// ================================ //
//
bool			Drawing::UpdatePenShader			( ResourceManager* rm, Brush* pen )
{
	return UpdateShaderImpl( rm, pen, m_penData );
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
	return false;
}

// ================================ //
//
bool			Drawing::UpdateVertexShader			( ResourceManager* rm, Geometry* geometry )
{
	return false;
}

// ================================ //
//
bool			Drawing::UpdateGeometry				( ResourceManager* rm, Geometry* geometry )
{
	if( geometry->NeedGeometryUpdate() )
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
	return false;
}

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
bool			Drawing::UpdateShaderImpl			( ResourceManager* rm, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->NeedShaderUpdate() )
	{
		assert( !"Implement me" );
		///@todo Shader must be composited from template part and part defined by brush. Write mechanism to do this.
		///@todo Think from where shaders should be loaded.

		brush->ShaderUpdated();
		return true;
	}

	return false;
}

// ================================ //
//
bool			Drawing::UpdateTextureImpl			( ResourceManager* rm, Brush* brush, impl::BrushRenderingData& brushData )
{
	if( brush->NeedTextureUpdate() )
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