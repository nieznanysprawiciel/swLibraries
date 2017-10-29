/**
@file PropertyRegistration.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "StructWithSimpleTypes.h"
#include "BaseObject.h"
#include "StringContainer.h"

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

	rttr::registration::class_< sw::BaseObject >( "BaseObject" )
		.property( "SimpleStruct1", &sw::BaseObject::m_simpleStruct1 ) BIND_AS_PTR;

	rttr::registration::class_< sw::DerivedObject >( "DerivedObject" )
		.property( "SimpleStruct2", &sw::DerivedObject::m_simpleStruct2 ) BIND_AS_REF;

	rttr::registration::class_< sw::StringContainer >( "StringContainer" )
		.property( "Description", &sw::StringContainer::Description )
		.property( "Content", &sw::StringContainer::Content );
}
