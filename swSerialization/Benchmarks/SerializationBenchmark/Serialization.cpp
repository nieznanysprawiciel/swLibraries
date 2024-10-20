/**
@file Serialization.cpp
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
static void		SerializeAndSaveFile	( benchmark::State& state )
{
	sw::Node root;
	root.GenerateTree( 100000, 20, TypeID::get< sw::BaseObject >() );

	for( auto _ : state )
	{
		sw::Serialization serial;
		serial.Serialize( "Serialization/Benchmarks/SimpleSerialization.xml", root );
	}
}


BENCHMARK( SerializeAndSaveFile )->Unit( benchmark::TimeUnit::kMillisecond )->Repetitions( 20 )->Iterations( 1 );



// ================================ //
//
static void		SerializeInternal	( benchmark::State& state )
{
	sw::Node root;
	root.GenerateTree( 100000, 20, TypeID::get< sw::BaseObject >() );

	for( auto _ : state )
	{
		sw::Serialization serial;
		ISerializer ser( std::static_pointer_cast< ISerializationContext >( std::make_shared< sw::SerializationContext >() ) );
		serial.Serialize( ser, root );
	}
}

BENCHMARK( SerializeInternal )->Unit( benchmark::TimeUnit::kMillisecond )->Repetitions( 20 )->Iterations( 1 );


