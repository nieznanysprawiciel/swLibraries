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
		FillWithDataset1();
	}

	void	FillWithDataset1	();
	void	FillWithDataset2	();
	void	FillWithDataset3	();
	void	FillWithDataset4	();
};


//====================================================================================//
//			Implementation
//====================================================================================//


// ================================ //
//
inline void		StructWithSimpleTypes::FillWithDataset1	()
{
	DoubleField = 1.0;
	FloatField = 2.0f;

	UIntField64 = 4;
	IntField64 = 5;
	UIntField32 = 6;
	IntField32 = -7;
	UIntField16 = 8;
	IntField16 = 9;
	UIntField8 = 10;
	IntField8 = 11;

	CharField = 'n';
	BoolField = false;
}

// ================================ //
//
inline void		StructWithSimpleTypes::FillWithDataset2	()
{
	DoubleField = 3.1111;
	FloatField = 1.4424141f;

	UIntField64 = 333;
	IntField64 = -33;
	UIntField32 = 1;
	IntField32 = 55;
	UIntField16 = 77;
	IntField16 = 22;
	UIntField8 = 99;
	IntField8 = 12;

	CharField = 'a';
	BoolField = true;
}

// ================================ //
//
inline void		StructWithSimpleTypes::FillWithDataset3	()
{
	DoubleField = 7.1231;
	FloatField = 10.4416141f;

	UIntField64 = 22;
	IntField64 = 222;
	UIntField32 = 2224;
	IntField32 = 95;
	UIntField16 = 12;
	IntField16 = -18;
	UIntField8 = -9;
	IntField8 = 5;

	CharField = 'k';
	BoolField = true;
}


// ================================ //
//
inline void		StructWithSimpleTypes::FillWithDataset4	()
{
	DoubleField = -13.1231;
	FloatField = -10.4416141f;

	UIntField64 = -22;
	IntField64 = -222;
	UIntField32 = -2224;
	IntField32 = -95;
	UIntField16 = -12;
	IntField16 = 88;
	UIntField8 = 87;
	IntField8 = 0;

	CharField = 'h';
	BoolField = false;
}


// ================================ //
//
inline bool		operator==		( const StructWithSimpleTypes& struct1, const StructWithSimpleTypes& struct2 )
{
	if( struct1.DoubleField != struct2.DoubleField )
		return false;

	if( struct1.FloatField != struct2.FloatField )
		return false;

	if( struct1.UIntField64 != struct2.UIntField64 )
		return false;

	if( struct1.IntField64 != struct2.IntField64 )
		return false;

	if( struct1.UIntField32 != struct2.UIntField32 )
		return false;

	if( struct1.IntField32 != struct2.IntField32 )
		return false;

	if( struct1.UIntField16 != struct2.UIntField16 )
		return false;

	if( struct1.IntField16 != struct2.IntField16 )
		return false;

	if( struct1.UIntField8 != struct2.UIntField8 )
		return false;

	if( struct1.IntField8 != struct2.IntField8 )
		return false;

	if( struct1.CharField != struct2.CharField )
		return false;

	if( struct1.BoolField != struct2.BoolField )
		return false;

	return true;
}

// ================================ //
//
inline bool		operator!=		( const StructWithSimpleTypes& struct1, const StructWithSimpleTypes& struct2 )
{
	return !( struct1 == struct2 );
}

}	// sw


