#include "Sizeofs.h"


#include "swCommonLib/Common/TypesDefinitions.h"


#include "swInputLibrary/InputCore/InputDeviceEvent.h"

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <string_view>
#include <string>
#include <optional>

#include "swGUI/Core/System/GUISystem.h"
#include "swGUI/Core/Controls/UIElement.h"
#include "swGUI/Core/Controls/FrameworkElement.h"
#include "swGUI/Core/Controls/Visual.h"

#include "swGUI/Core/Controls/Shapes/Rectangle.h"
#include "swGUI/Core/Controls/Shapes/Ellipse.h"
#include "swGUI/Core/Controls/TextualControls/TextBlock.h"

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
void			PrintSizeofType		( std::ostream& stream, std::string name = typeid( Type ).name() )
{
	stream << std::left;
	stream << std::setw( NameSize );
	stream << name;
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
    PrintSizeofType< sw::gui::FrameworkElement >( std::cout );
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
	PrintSizeofType< sw::gui::Ellipse >( std::cout );
    PrintSizeofType< sw::gui::TextBlock >( std::cout );
	
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
void			PrintStdSizeofs			    ()
{
    std::cout << std::left;
    std::cout << "Std Library:" << std::endl;
    std::cout << std::setw( NameSize ) << "Objects name" << "Sizeof" << std::endl;

    typedef std::string string;
    typedef std::wstring wstring;
    typedef std::string_view string_view;

    PrintSizeofType< std::filesystem::path >( std::cout );
    PrintSizeofType< std::string >( std::cout, "std::string" );
    PrintSizeofType< std::wstring >( std::cout, "std::wstring" );
    PrintSizeofType< std::string_view >( std::cout, "std::string_view" );
    PrintSizeofType< std::optional< int > >( std::cout );
    PrintSizeofType< std::optional< sw::gui::Brush* > >( std::cout );
    PrintSizeofType< std::function< void(int) > >( std::cout );

    std::cout << std::setw( NameSize ) << "std::enable_shared_from_this additional size" << ( sizeof( VirtualEmptyClass ) - sizeof( VirtualEmptyClass* ) ) << std::endl;

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
	PrintSizeofType< sw::input::KeyEvent >( std::cout );
    PrintSizeofType< fastdelegate::FastDelegate1< int > >( std::cout );

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
    PrintStdSizeofs();
}
