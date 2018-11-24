#include "swCommonLib/External/Catch/catch.hpp"

#include "swCommonLib/Common/Exceptions/ErrorsCollector.h"
#include "swCommonLib/Common/Exceptions/ExceptionsList.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"


using namespace sw;


// ================================ //
//
ReturnResult		FunctionWithException		( bool returnException )
{
	if( returnException )
		return std::make_shared< RuntimeException >( "[Error] Something gone wrong." );

	return Result::Success;
}



// ================================ //
// ErrorsCollector with no exceptions appended should return valid ReturnResult.
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.NoExceptions" )
{
	ErrorsCollector collector;

	CHECK( static_cast< ReturnResult >( collector ).IsValid() );
}

// ================================ //
// ErrorsCollector sould return success after adding success result.
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.SuccessResultAdded" )
{
	ErrorsCollector collector;
	collector.Add( FunctionWithException( false ) );

	CHECK( static_cast< ReturnResult >( collector ).IsValid() );
}

// ================================ //
// If we first add success then exception, we should get invalid result.
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.Success+Exception" )
{
	ErrorsCollector collector;
	collector.Add( FunctionWithException( false ) );
	collector.Add( FunctionWithException( true ) );

	CHECK( !static_cast< ReturnResult >( collector ).IsValid() );
	CHECK( !collector.IsList() );
}

// ================================ //
// If we first add exception then success, we should get invalid result.Success shouldn't override previous exceptions.
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.Exception+Success" )
{
	ErrorsCollector collector;
	collector.Add( FunctionWithException( true ) );
	collector.Add( FunctionWithException( false ) );

	CHECK( !static_cast< ReturnResult >( collector ).IsValid() );
	CHECK( !collector.IsList() );
}

// ================================ //
// If we add 2 exceptions we should get invalid result and ExceptionsList created inside.
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.2Exceptions" )
{
	ErrorsCollector collector;
	collector.Add( FunctionWithException( true ) );
	collector.Add( FunctionWithException( true ) );

	CHECK( !static_cast< ReturnResult >( collector ).IsValid() );
	CHECK( collector.IsList() );
	CHECK( collector.GetExceptionsList() != nullptr );
}

// ================================ //
// If we add 3 exceptions we should get invalid result and ExceptionsList created inside.
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.3Exceptions" )
{
	ErrorsCollector collector;
	collector.Add( FunctionWithException( true ) );
	collector.Add( FunctionWithException( true ) );
	collector.Add( FunctionWithException( true ) );

	CHECK( !static_cast< ReturnResult >( collector ).IsValid() );
	CHECK( collector.IsList() );
	CHECK( collector.GetExceptionsList() != nullptr );
}
