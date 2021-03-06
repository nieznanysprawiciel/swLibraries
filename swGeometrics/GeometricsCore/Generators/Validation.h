#pragma once
/**
@file Validation.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"

#include "swGeometrics/GeometricsCore/Types/Traits/GeneratorTraits.h"
#include "swGeometrics/GeometricsCore/Types/Traits/ProcessorTraits.h"

#include <type_traits>


namespace sw {
namespace geom
{

namespace impl
{

// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator >
typename std::enable_if< isGenerator< Generator >::value, void >::type
						CompileTimeValidation		( const Generator& gen );

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor >
typename std::enable_if< isProcessor< Processor >::value, void >::type
						CompileTimeValidation		( const Processor& processor );

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor, typename... Processors >
typename std::enable_if< isProcessor< Processor >::value, void >::type
						CompileTimeValidation		( const Processor& processor, const Processors&... processors );

// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator, typename... Processors >
typename std::enable_if< isGenerator< Generator >::value, void >::type
						CompileTimeValidation		( const Generator& gen, const Processors&... processors );



// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator, typename... Processors >
typename std::enable_if< isGenerator< Generator >::value, ReturnResult >::type
						RuntimeValidation			( const Generator& gen, const Processors&... processors );

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor >
ErrorsCollector			RuntimeValidation			( Processor processor );

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor, typename... Processors >
typename std::enable_if< isProcessor< Processor >::value, ErrorsCollector >::type
						RuntimeValidation			( Processor processor, const Processors&... processors );

}	// impl


// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator, typename... Processors >
ReturnResult			Validate					( const Generator& gen, const Processors&... processors );




//====================================================================================//
//			Implementation
//====================================================================================//


namespace impl
{

// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator >
typename std::enable_if< isGenerator< Generator >::value, void >::type
						CompileTimeValidation				( const Generator& gen )
{
	static_assert( std::is_same< typename Generator::VertexFormat, VertexType >::value, "Generator should have the same VertexType as Generate function." );
	static_assert( std::is_same< typename Generator::IndexFormat, IndexType >::value, "Generator should have the same VertexType as Generate function." );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor >
typename std::enable_if< isProcessor< Processor >::value, void >::type
						CompileTimeValidation				( const Processor& processor )
{
	static_assert( std::is_same< typename Processor::VertexFormat, VertexType >::value, "Processor should have the same VertexType as Generate function." );

	// Add static asserts here
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor, typename... Processors >
typename std::enable_if< isProcessor< Processor >::value, void >::type
						CompileTimeValidation				( const Processor& processor, const Processors& ...processors )
{
	CompileTimeValidation< VertexType, IndexType, Processor >( processor );
	CompileTimeValidation< VertexType, IndexType >( processors... );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator, typename... Processors >
typename std::enable_if< isGenerator< Generator >::value, void >::type
						CompileTimeValidation				( const Generator& gen, const Processors&... processors )
{
	CompileTimeValidation< VertexType, IndexType, Generator >( gen );
	CompileTimeValidation< VertexType, IndexType >( processors... );
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator, typename ...Processors >
typename std::enable_if< isGenerator< Generator >::value, ReturnResult >::type
						RuntimeValidation					( const Generator& gen, const Processors&... processors )
{
	ErrorsCollector collector;

	if( gen.GetNumberVerticies() >= std::numeric_limits< IndexType >::max() )
		collector.Add( ReturnResult( "Too many verticies for required IndexType." ) );

	collector.Add( gen.ValidateParams() );
	collector.Add( RuntimeValidation< VertexType, IndexType >( processors... ) );

	return collector;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor >
ErrorsCollector			RuntimeValidation					( Processor processor )
{
	ErrorsCollector collector;
	collector.Add( processor.ValidateParams() );

	return collector;
}

// ================================ //
//
template< typename VertexType, typename IndexType, typename Processor, typename ...Processors >
typename std::enable_if< isProcessor< Processor >::value, ErrorsCollector >::type
						RuntimeValidation					( Processor processor, const Processors&... processors )
{
	auto collector = RuntimeValidation< VertexType, IndexType >( processor );
	collector.Add( RuntimeValidation< VertexType, IndexType >( processors... ) );

	return collector;
}

}	// impl


// ================================ //
//
template< typename VertexType, typename IndexType, typename Generator, typename ...Processors >
ReturnResult			Validate					( const Generator& gen, const Processors&... processors )
{
	impl::CompileTimeValidation< VertexType, IndexType >( gen, processors... );
	return impl::RuntimeValidation< VertexType, IndexType >( gen, processors... );
}

}	// geom
}	// sw


