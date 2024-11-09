#pragma once
/**
@file FrameworkElement.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGUI/Core/Controls/UIElement.h"

namespace sw {
namespace gui
{

/**@brief Provides a framework-level set of properties.

@todo This class is empty for now, but in the future it should reflect WPF
functionalities of FrameworkElement*/
class FrameworkElement : public UIElement
{
    RTTR_ENABLE( UIElement );
    RTTR_REGISTRATION_FRIEND;

private:
protected:
public:
    explicit FrameworkElement() = default;
    virtual ~FrameworkElement() = default;

public:
    virtual Size    GetNumChildren() const override;
    virtual Visual* GetVisualChild( Size idx ) const override;
    virtual Size2D  Measure( Size2D availableSize ) override;
    virtual void    Arrange( Rect& finalRect ) override;
    virtual bool    AddChild( UIElementOPtr&& child ) override;
};


}  // gui
}	// sw


