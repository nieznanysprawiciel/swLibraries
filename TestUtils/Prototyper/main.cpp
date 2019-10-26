#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Node.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/BaseObject.h"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"
#include "swCommonLib/Serialization/PropertySerialization/SerializationContext.h"


#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/LinkLibrary.h"
auto pullInLibrary = sw::LinkPrimitivesRegistration();




int main()
{
	sw::Node root;
	root.GenerateTree( 100000, 20, TypeID::get< sw::BaseObject >() );

	sw::Serialization serial;
	serial.Serialize( "Serialization/Benchmarks/BenchmarkTree.xml", root );

	IDeserializer deser( std::make_shared< sw::SerializationContext >() );
	deser.LoadFromFile( "Serialization/Benchmarks/BenchmarkTree.xml", ParsingMode::ParseInsitu );

	sw::Node object;

	sw::Serialization deserial;
	deserial.Deserialize< sw::Node >( deser, object );
}

