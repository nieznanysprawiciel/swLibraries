/**
@file PropertyRegistration.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "StructWithSimpleTypes.h"

#include "swCommonLib/Common/RTTR.h"



RTTR_REGISTRATION
{

	rttr::registration::class_< sw::StructWithSimpleTypes >( "StructWithSimpleTypes" )
		.property( "DoubleField", &sw::StructWithSimpleTypes::DoubleField )
		.property( "FloatField", &sw::StructWithSimpleTypes::FloatField )
		.property( "UIntField64", &sw::StructWithSimpleTypes::UIntField64 )
		.property( "IntField64", &sw::StructWithSimpleTypes::IntField64 )
		.property( "UIntField32", &sw::StructWithSimpleTypes::UIntField32 )
		.property( "IntField32", &sw::StructWithSimpleTypes::IntField32 )
		.property( "UIntField16", &sw::StructWithSimpleTypes::UIntField16 )
		.property( "IntField16", &sw::StructWithSimpleTypes::IntField16 )
		.property( "UIntField8", &sw::StructWithSimpleTypes::UIntField8 )
		.property( "IntField8", &sw::StructWithSimpleTypes::IntField8 )
		.property( "CharField", &sw::StructWithSimpleTypes::CharField )
		.property( "BoolField", &sw::StructWithSimpleTypes::BoolField );
}
