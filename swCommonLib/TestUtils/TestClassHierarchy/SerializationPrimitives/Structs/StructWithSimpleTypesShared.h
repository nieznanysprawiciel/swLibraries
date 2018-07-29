#pragma once

#include "StructWithSimpleTypes.h"


namespace sw
{

// ================================ //
//
struct StructWithSimpleTypesShared : public StructWithSimpleTypes
{
	explicit StructWithSimpleTypesShared() {}
};

DEFINE_PTR_TYPE( StructWithSimpleTypesShared )

}	// sw


