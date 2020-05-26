/**
@file Deserialization.cpp
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include "benchmark/benchmark.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Node.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Polymorphic/BaseObject.h"

#include "swSerialization/Serialization/Serialization.h"
#include "swSerialization/Serialization/SerializationContext.h"



// ================================ //
//
static void		DeserializeFromDisk			( benchmark::State& state )
{
	sw::Node root;
	root.GenerateTree( 100000, 20, TypeID::get< sw::BaseObject >() );

	sw::Serialization serial;
	serial.Serialize( "Serialization/Benchmarks/BenchmarkTree.xml", root );

	for( auto _ : state )
	{
		sw::Node object;

		sw::Serialization deserial;
		deserial.Deserialize< sw::Node >( "Serialization/Benchmarks/BenchmarkTree.xml", object );
	}
}


BENCHMARK( DeserializeFromDisk )->Unit( benchmark::TimeUnit::kMillisecond )->Repetitions( 20 )->Iterations( 1 );



// ================================ //
//
static void		DeserializeInternal			( benchmark::State& state )
{
	sw::Node root;
	root.GenerateTree( 100000, 20, TypeID::get< sw::BaseObject >() );

	sw::Serialization serial;
	serial.Serialize( "Serialization/Benchmarks/BenchmarkTree.xml", root );

	IDeserializer deser( std::make_shared< sw::SerializationContext >() );
	deser.LoadFromFile( "Serialization/Benchmarks/BenchmarkTree.xml" );

	for( auto _ : state )
	{
		sw::Node object;

		sw::Serialization deserial;
		deserial.Deserialize< sw::Node >( deser, object );
	}
}

BENCHMARK( DeserializeInternal )->Unit( benchmark::TimeUnit::kMillisecond )->Repetitions( 20 )->Iterations( 1 );


