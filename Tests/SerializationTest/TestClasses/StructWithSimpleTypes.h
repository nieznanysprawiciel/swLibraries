#pragma once
/**
@file StructWithSimpleTypes.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "swCommonLib/Common/TypesDefinitions.h"


namespace sw
{

// ================================ //
//
struct StructWithSimpleTypes
{
	double		DoubleField;
	float		FloatField;

	uint64		UIntField64;
	int64		IntField64;
	uint32		UIntField32;
	int32		IntField32;
	uint16		UIntField16;
	int16		IntField16;
	uint8		UIntField8;
	int8		IntField8;

	char		CharField;
	bool		BoolField;

// ================================ //
//
	StructWithSimpleTypes()
	{
		DoubleField = 1.0;
		FloatField = 2.0;

		UIntField64 = 4;
		IntField64 = 4;
		UIntField32 = 4;
		IntField32 = 4;
		UIntField16 = 4;
		IntField16 = 4;
		UIntField8 = 4;
		IntField8 = 4;

		CharField = 4;
		BoolField = false;
	}
};


}	// sw


