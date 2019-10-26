/**
@file PropertyRegistration.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/



#include "StringContainer.h"

#include "Arrays/ArrayContainer.h"
#include "Arrays/ArrayPolymorphicContainer.h"
#include "Arrays/StaticArrayContainer.h"
#include "Arrays/StaticArrayContainer_Readonly.h"

#include "Enums/TriStateEnum.h"
#include "Enums/TriStateObject.h"

#include "Structs/StructWithSimpleTypes.h"
#include "Structs/StructAsRefContainer.h"
#include "Structs/StructAsPtrContainer.h"
#include "Structs/StructAsCopyContainer.h"
#include "Structs/StructPtrContainer.h"
#include "Structs/StructSharedPtrContainer.h"

#include "Structs/StructWithSimpleTypesShared.h"

#include "Polymorphic/BaseObject.h"
#include "Polymorphic/SharedObject.h"
#include "Polymorphic/PolymorphicObjectContainer.h"
#include "Polymorphic/PolymorphicSharedPtrContainer.h"

#include "Node.h"


#include "swCommonLib/Common/RTTR.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/LinkLibrary.h"



RTTR_REGISTRATION
{

	rttr::registration::enumeration< sw::TriStateEnum >( "TriStateEnum" )
		(
		  rttr::value( "Down",      sw::TriStateEnum::Down ),
		  rttr::value( "Middle",    sw::TriStateEnum::Middle ),
		  rttr::value( "Up",		sw::TriStateEnum::Up )
		 );

	rttr::registration::class_< sw::TriStateObject >( "TriStateObject" )
		.property( "State", &sw::TriStateObject::State );

	rttr::registration::class_< sw::StructAsRefContainer >( "StructAsRefContainer" )
		.property( "SimpleStruct", &sw::StructAsRefContainer::SimpleStruct ) BIND_AS_REF;

	rttr::registration::class_< sw::StructAsPtrContainer >( "StructAsPtrContainer" )
		.property( "SimpleStruct", &sw::StructAsPtrContainer::SimpleStruct ) BIND_AS_PTR;

	rttr::registration::class_< sw::StructAsCopyContainer >( "StructAsCopyContainer" )
		.property( "SimpleStruct", &sw::StructAsCopyContainer::SimpleStruct );

	rttr::registration::class_< sw::StructPtrContainer >( "StructPtrContainer" )
		.property( "SimpleStruct", &sw::StructPtrContainer::SimpleStruct );

	rttr::registration::class_< sw::StructSharedPtrContainer >( "StructSharedPtrContainer" )
		.property( "SimpleStruct", &sw::StructSharedPtrContainer::SimpleStruct );

	rttr::registration::class_< sw::StructWithSimpleTypes >( "StructWithSimpleTypes" )
		.constructor<>()	( rttr::policy::ctor::as_raw_ptr )
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

	rttr::registration::class_< sw::StructWithSimpleTypesShared >( "StructWithSimpleTypesShared" )
		.constructor<>()	( rttr::policy::ctor::as_std_shared_ptr )
		.property( "DoubleField", &sw::StructWithSimpleTypesShared::DoubleField )
		.property( "FloatField", &sw::StructWithSimpleTypesShared::FloatField )
		.property( "UIntField64", &sw::StructWithSimpleTypesShared::UIntField64 )
		.property( "IntField64", &sw::StructWithSimpleTypesShared::IntField64 )
		.property( "UIntField32", &sw::StructWithSimpleTypesShared::UIntField32 )
		.property( "IntField32", &sw::StructWithSimpleTypesShared::IntField32 )
		.property( "UIntField16", &sw::StructWithSimpleTypesShared::UIntField16 )
		.property( "IntField16", &sw::StructWithSimpleTypesShared::IntField16 )
		.property( "UIntField8", &sw::StructWithSimpleTypesShared::UIntField8 )
		.property( "IntField8", &sw::StructWithSimpleTypesShared::IntField8 )
		.property( "CharField", &sw::StructWithSimpleTypesShared::CharField )
		.property( "BoolField", &sw::StructWithSimpleTypesShared::BoolField );

	rttr::registration::class_< sw::BaseObject >( "BaseObject" )
		.constructor<>()	( rttr::policy::ctor::as_raw_ptr )
		.property( "SimpleStruct1", &sw::BaseObject::m_simpleStruct1 ) BIND_AS_PTR;

	rttr::registration::class_< sw::DerivedObject >( "DerivedObject" )
		.constructor<>()	( rttr::policy::ctor::as_raw_ptr )
		.property( "SimpleStruct2", &sw::DerivedObject::m_simpleStruct2 ) BIND_AS_PTR;

	rttr::registration::class_< sw::SharedObject >( "SharedObject" )
		.constructor<>()	( rttr::policy::ctor::as_std_shared_ptr )
		.property( "SimpleStruct2", &sw::SharedObject::m_simpleStruct2 ) BIND_AS_PTR;

	rttr::registration::class_< sw::DerivedFromSharedObject >( "DerivedFromSharedObject" )
		.constructor<>()	( rttr::policy::ctor::as_raw_ptr );

	rttr::registration::class_< sw::NotRelated >( "NotRelated" )
		.constructor<>()	( rttr::policy::ctor::as_raw_ptr )
		.property( "SimpleStruct1", &sw::BaseObject::m_simpleStruct1 ) BIND_AS_PTR;

	rttr::registration::class_< sw::PolymorphicObjectContainer >( "PolymorphicObjectContainer" )
		.property( "ObjectPtr", &sw::PolymorphicObjectContainer::ObjectPtr );

	rttr::registration::class_< sw::PolymorphicSharedPtrContainer >( "PolymorphicSharedPtrContainer" )
		.property( "ObjectPtr", &sw::PolymorphicSharedPtrContainer::ObjectPtr );

	rttr::registration::class_< sw::StringContainer >( "StringContainer" )
		.constructor<>()	( rttr::policy::ctor::as_raw_ptr )
		.property( "Description", &sw::StringContainer::Description )
		.property( "Content", &sw::StringContainer::Content );

	rttr::registration::class_< std::vector< sw::StructWithSimpleTypes > >( "StructWithSimpleTypesVec" );

	rttr::registration::class_< sw::ArrayContainer >( "ArrayContainer" )
		.property( "StructsVec", &sw::ArrayContainer::StructsVec ) BIND_AS_REF;

	rttr::registration::class_< sw::ArrayPolymorphicContainer >( "ArrayPolymorphicContainer" )
		.property( "PolymorphicsVec", &sw::ArrayPolymorphicContainer::PolymorphicsVec ) BIND_AS_REF;

	rttr::registration::class_< sw::StaticArrayContainer >( "StaticArrayContainer" )
		.property( "StructsVec", &sw::StaticArrayContainer::StructsVec );

	rttr::registration::class_< sw::StaticArrayContainer_Readonly >( "StaticArrayContainer_Readonly" )
		.property_readonly( "StructsVec", &sw::StaticArrayContainer_Readonly::StructsVec ) BIND_AS_REF;

	rttr::registration::class_< sw::Node >( "Node" )
		.property( "Children", &sw::Node::Children ) BIND_AS_REF
		.property( "Generic", &sw::Node::Generic );
}


namespace sw
{


// ================================ //
// Add this function to pull registration code into library.
int			LinkPrimitivesRegistration()
{
	return 0;
}


}	// sw
