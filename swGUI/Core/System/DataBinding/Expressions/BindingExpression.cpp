/**
@file BindingExpression.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/
#include "swGUI/Core/stdafx.h"


#include "BindingExpression.h"

#include "swCommonLib/Common/Properties/Properties.h"



namespace sw {
namespace gui
{

  // ================================ //
//
Nullable< BindingTarget >				BindingExpression::EvaluateRelativeProperty		( const rttr::variant & dataContext, const std::string & path )
{
	auto propObjPair = Properties::GetProperty( dataContext, path, 0, '.' );

	// Check only target object for existance.
	if( propObjPair.first.is_valid() )
		return BindingTarget( propObjPair.first, propObjPair.second );

	/// @todo Make exception for this error.
	return Nullable< BindingTarget >();
}




}	// gui
}	// sw


