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

// ================================ //
// 
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.AddExceptionsList" )
{
	ErrorsCollector collector;
	ExceptionsListPtr list = std::make_shared< ExceptionsList >();
	
	list->AddException( FunctionWithException( true ).GetError() );
	list->AddException( FunctionWithException( true ).GetError() );
	list->AddException( FunctionWithException( true ).GetError() );

	collector.Add( list );

	CHECK( !static_cast< ReturnResult >( collector ).IsValid() );
	CHECK( collector.IsList() );
	CHECK( collector.GetExceptionsList() != nullptr );
}

// ================================ //
// 
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.AddExceptionsListToExisitngExceptions" )
{
	ErrorsCollector collector;
	ExceptionsListPtr list = std::make_shared< ExceptionsList >();
	
	collector.Add( FunctionWithException( true ) );

	list->AddException( FunctionWithException( true ).GetError() );
	list->AddException( FunctionWithException( true ).GetError() );
	list->AddException( FunctionWithException( true ).GetError() );

	collector.Add( list );

	CHECK( !static_cast< ReturnResult >( collector ).IsValid() );
	CHECK( collector.IsList() );
	CHECK( collector.GetExceptionsList() != nullptr );
	CHECK( collector.GetExceptionsList()->GetNestedExceptions().size() == 4 );
}

// ================================ //
// 
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.MergeCollectors" )
{
	ErrorsCollector collector1;
	ErrorsCollector collector2;
	
	collector1.Add( FunctionWithException( true ) );
	collector1.Add( FunctionWithException( true ) );
	collector1.Add( FunctionWithException( true ) );

	collector2.Add( FunctionWithException( true ) );
	collector2.Add( FunctionWithException( true ) );

	collector1.Add( collector2 );

	CHECK( !static_cast< ReturnResult >( collector1 ).IsValid() );
	CHECK( collector1.IsList() );
	CHECK( collector1.GetExceptionsList() != nullptr );
	CHECK( collector1.GetExceptionsList()->GetNestedExceptions().size() == 5 );
}

// ================================ //
// If you add ErrorsCollector to itself it should do nothing.
TEST_CASE( "Common.Helpers.Exceptions.ErrorsCollector.AddCollectorToItself" )
{
	ErrorsCollector collector;
	collector.Add( FunctionWithException( true ) );
	collector.Add( FunctionWithException( true ) );

	collector.Add( collector );

	CHECK( !static_cast< ReturnResult >( collector ).IsValid() );
	CHECK( collector.GetExceptionsList()->GetNestedExceptions().size() == 2 );
}

