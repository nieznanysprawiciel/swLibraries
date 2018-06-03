#include "benchmark/benchmark.h"

#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/Node.h"
#include "swCommonLib/TestUtils/TestClassHierarchy/SerializationPrimitives/StringContainer.h"

#include "swCommonLib/Serialization/PropertySerialization/Serialization.h"



// ================================ //
//
static void		Serialization	( benchmark::State& state )
{
	sw::Node root;
	root.GenerateTree( 10000, 20, TypeID::get< sw::StringContainer >() );

	for( auto _ : state )
	{
		sw::Serialization serial;
		serial.Serialize( "Serialization/Benchmarks/SimpleSerialization.xml", root );
	}
}


BENCHMARK( Serialization )->Unit( benchmark::TimeUnit::kMillisecond )->Repetitions( 20 )->Iterations( 1 );
