/**
@file Visual.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"



namespace sw {
namespace gui
{

// ================================ //
//
Visual::Visual()
	:	m_offset( Position( 0.0f, 0.0f ) )
{}

// ================================ //
//
void            Visual::SetWidth        ( float width )
{
    m_size.x = width;
}

// ================================ //
//
void            Visual::SetHeight       ( float height )
{
    m_size.y = height;
}


}	// gui
}	// sw

