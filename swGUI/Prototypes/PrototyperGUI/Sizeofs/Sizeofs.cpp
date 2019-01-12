#include "Sizeofs.h"


#include "swCommonLib/Common/TypesDefinitions.h"


#include "swInputLibrary/InputCore/InputDeviceEvent.h"

#include <iostream>
#include <iomanip>


#include "swGUI/Core/System/GUISystem.h"
#include "swGUI/Core/Controls/UIElement.h"
#include "swGUI/Core/Controls/Visual.h"

#include "swGUI/Core/Controls/Shapes/Rectangle.h"

#include "swGUI/Core/System/DataBinding/BindingInfo.h"

#include "swGUI/Core/Media/Media.h"



class VirtualEmptyClass : std::enable_shared_from_this< VirtualEmptyClass >
{

	virtual ~VirtualEmptyClass() { }
};



const int NameSize = 60;


// ================================ //
//
template< typename Type >
void			PrintSizeofType		( std::ostream& stream )
{
	stream << std::left;
	stream << std::setw( NameSize );
	stream << typeid( Type ).name();
	stream << sizeof( Type ) << std::endl;
}

// ================================ //
//
void			PrintGUIElementsSizeofs		()
{
	std::cout << std::left;
	std::cout << "GUI Elements:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name"  << "Sizeof" << std::endl;

	PrintSizeofType< sw::gui::DependencyObject >( std::cout );
	PrintSizeofType< sw::gui::Visual >( std::cout );
	PrintSizeofType< sw::gui::UIElement >( std::cout );
	PrintSizeofType< sw::gui::HostWindow >( std::cout );

	std::cout << std::endl;
}

// ================================ //
//
void			PrintControlsSizeofs		()
{
	std::cout << std::left;
	std::cout << "Controls:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name"  << "Sizeof" << std::endl;

	PrintSizeofType< sw::gui::Shape >( std::cout );
	PrintSizeofType< sw::gui::Rectangle >( std::cout );

	std::cout << std::endl;
}

// ================================ //
//
void			PrintMediaSizeofs			()
{
	std::cout << std::left;
	std::cout << "Media:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name"  << "Sizeof" << std::endl;

	PrintSizeofType< sw::gui::Brush >( std::cout );
	PrintSizeofType< sw::gui::SolidColorBrush >( std::cout );

	PrintSizeofType< sw::gui::RectangleGeometry >( std::cout );

	std::cout << std::endl;
}

// ================================ //
//
void			PrintGUIInternalsSizeofs	()
{
	std::cout << std::left;
	std::cout << "GUI Internal objects:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name"  << "Sizeof" << std::endl;

	PrintSizeofType< sw::gui::BindingInfo >( std::cout );
	PrintSizeofType< sw::gui::Binding >( std::cout );
	PrintSizeofType< sw::gui::BindingExpression >( std::cout );

	std::cout << std::endl;
}

// ================================ //
//
void			PrintRTTRTypesSizeofs		()
{
	std::cout << std::left;
	std::cout << "RTTR types:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name" << "Sizeof" << std::endl;

	PrintSizeofType< rttr::variant >( std::cout );
	PrintSizeofType< rttr::instance >( std::cout );
	PrintSizeofType< rttr::property >( std::cout );
	PrintSizeofType< rttr::type >( std::cout );
	PrintSizeofType< rttr::method >( std::cout );

	std::cout << std::endl;
}

// ================================ //
//
void			PrintOtherSizeofs			()
{
	std::cout << std::left;
	std::cout << "Other:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name" << "Sizeof" << std::endl;
	
	PrintSizeofType< sw::input::DeviceEvent >( std::cout );
	PrintSizeofType< sw::input::AxisEvent >( std::cout );
	PrintSizeofType< sw::input::ButtonEvent >( std::cout );
	PrintSizeofType< sw::input::CursorEvent >( std::cout );
	PrintSizeofType< sw::input::KeyEvent>( std::cout );

	std::cout << std::setw( NameSize ) << "std::enable_shared_from_this additional size" << ( sizeof( VirtualEmptyClass ) - sizeof( VirtualEmptyClass* ) ) << std::endl;

	std::cout << std::endl;
}

// ================================ //
//
void			PrintSizeofs				()
{
	PrintGUIElementsSizeofs();
	PrintControlsSizeofs();
	PrintMediaSizeofs();
	PrintGUIInternalsSizeofs();
	PrintRTTRTypesSizeofs();
	PrintOtherSizeofs();
}
