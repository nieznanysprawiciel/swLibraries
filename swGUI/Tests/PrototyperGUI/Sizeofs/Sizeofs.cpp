#include "Sizeofs.h"


#include "swCommonLib/Common/TypesDefinitions.h"


#include "swInputLibrary/InputCore/InputDeviceEvent.h"

#include <iostream>
#include <iomanip>


#include "swGUI/Core/System/GUISystem.h"
#include "swGUI/Core/Controls/IControl.h"
#include "swGUI/Core/Controls/UIElement.h"
#include "swGUI/Core/Controls/Visual.h"

#include "swGUI/Core/System/DataBinding/BindingInfo.h"



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
void			PrintSizeofs()
{
	std::cout << std::left;
	std::cout << "GUI Elements:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name"  << "Sizeof" << std::endl;

	PrintSizeofType< sw::gui::IControl >( std::cout );
	PrintSizeofType< sw::gui::Visual >( std::cout );
	PrintSizeofType< sw::gui::UIElement >( std::cout );

	std::cout << std::left;
	std::cout << std::endl << "GUI Internal objects:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name"  << "Sizeof" << std::endl;

	PrintSizeofType< sw::gui::BindingsInfo >( std::cout );
	PrintSizeofType< sw::gui::Binding >( std::cout );
	PrintSizeofType< sw::gui::BindingExpression >( std::cout );
	

	std::cout << std::endl << "RTTR types:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name" << "Sizeof" << std::endl;

	PrintSizeofType< rttr::variant >( std::cout );
	PrintSizeofType< rttr::instance >( std::cout );
	PrintSizeofType< rttr::property >( std::cout );
	PrintSizeofType< rttr::type >( std::cout );
	PrintSizeofType< rttr::method >( std::cout );

	std::cout << std::endl << "Other:" << std::endl;
	std::cout << std::setw( NameSize ) << "Objects name" << "Sizeof" << std::endl;
	
	PrintSizeofType< sw::input::DeviceEvent >( std::cout );
	PrintSizeofType< sw::input::AxisEvent >( std::cout );
	PrintSizeofType< sw::input::ButtonEvent >( std::cout );
	PrintSizeofType< sw::input::CursorEvent >( std::cout );
	PrintSizeofType< sw::input::KeyEvent>( std::cout );


	std::cout << std::setw( NameSize ) << "std::enable_shared_from_this additional size" << ( sizeof( VirtualEmptyClass ) - sizeof( VirtualEmptyClass* ) ) << std::endl;
}
