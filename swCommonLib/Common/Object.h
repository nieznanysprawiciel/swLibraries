#pragma once
/**
@file Object.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/Common/TypesDefinitions.h"

/**@mainpage

@section Mainpage_LibraryFunctionalities Library functionalities

- @ref Page_Serialization "Serialization"
- @ref HierarchicalChunkedFormat "Hierarchical Chunked Format"
- @ref KeyFrameAnimation "Parameters Animation"

@section MainPage_Usage Using libraries

Note that libraries are still in development process.

- Add <b>CommonLibraries.sln</b> solution file to your solution. (Add->Existing Project, then choose <b>CommonLibraries.sln</b> file. This operation
will merge two solutions. You must change files filter to see .sln files in browser.)
- Add parent directory of swCommonLib to Additional Include Directories.
- In project that will use one of libraries choose <b>Add Reference</b> and add necessary libraries.
- From <b>swCommonLib/Projects/Visual2015/ </b> directory add <b>LinkReflection.props</b> and <b>Paths.props</b> to project which builds executable.
This will copy Reflection.dll to your output directory.

*/




/**@brief Base class for all objects in sleeping wombat libraries.

@todo Move to sw namespace.

@ingroup Reflection*/
class Object
{
	RTTR_ENABLE()

public:

	inline TypeID		GetType			() const		{ return this->get_type(); }
	inline std::string	GetTypeName		() const		{ return std::string( this->get_type().get_name() ); }


	/**@brief Returns memory size possesed by this class and all it's nested objects.
	Result should be computed recursivly.*/
	virtual Size		MemorySize		() const;

	template< typename TargetType >
	TargetType*			DynamicCast		()							{ return rttr::rttr_cast< TargetType* >( this ); }
};

