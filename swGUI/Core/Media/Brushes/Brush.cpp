#include "Brush.h"



namespace sw {
namespace gui
{

// ================================ //
//
void			Brush::InvalidateConstants		()
{
	m_invalidateConstants = true;
}

// ================================ //
//
void			Brush::InvalidateShader			()
{
	m_invalidateShader = true;
}

// ================================ //
//
void			Brush::InvalidateTexture		()
{
	m_invalidateTexture = true;
}

// ================================ //
//
void			Brush::ShaderUpdated			()
{
	m_invalidateShader = false;
}

// ================================ //
//
void			Brush::TextureUpdated			()
{
	m_invalidateTexture = false;
}

// ================================ //
//
void			Brush::ConstantsUpdated			()
{
	m_invalidateConstants = false;
}

}	// gui
}	// sw