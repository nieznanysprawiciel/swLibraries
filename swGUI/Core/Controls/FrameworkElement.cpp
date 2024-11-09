/**
@file FrameworkElement.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"

#include "swGUI/Core/Controls/FrameworkElement.h"

namespace sw {
namespace gui
{

    
// ================================ //
//
Size            FrameworkElement::GetNumChildren() const
{
    return 0;
}

// ================================ //
//
Visual*         FrameworkElement::GetVisualChild( Size idx ) const
{
    // No children.
    return nullptr;
}

// ================================ //
//
Size2D          FrameworkElement::Measure( Size2D availableSize )
{
    assert( !"Implement me" );
    return Size2D();
}

// ================================ //
//
void            FrameworkElement::Arrange( Rect& finalRect ) { assert( !"Implement me" ); }

// ================================ //
//
bool            FrameworkElement::AddChild( UIElementOPtr&& child )
{
    return false;
}



}  // namespace gui
}  // namespace sw
