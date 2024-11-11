#pragma once
/**@file PerformanceCheck.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
@brief Contains the declaration of the PerformanceCheck class, which is used to measure the time spent on executing selected tasks.
*/

#include <string>
#include <vector>
#include "swCommonLib/Common/TypesDefinitions.h"




namespace sw
{


/**@brief Structure that stores performance data for a single measured task.*/
struct _PerformanceData
{
	uint64				LastStartTime;				///<Last recorded time for the measured task.
	uint64				WholeTime;					///<Total time spent on executing the task.
	uint64				MinTime;					///<Minimum execution time of the task.
	uint64				MaxTime;					///<Maximum execution time of the task.
	uint32				NumExecutions;				///<Number of times the task was executed - number of even calls to StartPerformanceCheck and EndPerformanceCheck.
	std::string			TaskName;					///<Name of the task that will be displayed in the statistics.
};;

/**@brief The class is used to measure the performance of individual code segments.

Usage of the class:
There are two methods. You can normally use the class as a regular object and call its functions,
or you can use specially defined macros instead. In the second case, the code used for measurement will
be included only if the PERFORMANCE_CHECK macro is defined. Otherwise, all used macros will
expand to empty instructions.

1. Normal use of the class.
Each task must be surrounded by calls to the StartPerformanceCheck and EndPerformanceCheck functions with the task index provided.

To print the results, call the printPerformanceStatisticsAsync function providing the name of the file to which the statistics will be sent.
The function works asynchronously, so it does not wait for the file to be saved, but continues executing the engine code.

\code
#include PerformanceCheck.h

unsigned int taskID;
PerformanceCheck stats;

myClass::myClass()
{
	taskID = stats.RegisterTaskName("TaskName");
}

void timer()
{
	stats.StartPerformanceCheck(taskID);

	// Here is the code whose performance we are measuring

	stats.EndPerformanceCheck(taskID);
}

\endcode

2. Using the class with macros.
To use the class, define the PERFORMANCE_CHECK macro before including the header.
This macro does two things:
- enables the definitions of other necessary macros
- includes the code creating an object of this class (the object is a global variable in the PerformanceCheck.cpp file)

At the measurement point, call the START_PERFORMANCE_CHECK and END_PERFORMANCE_CHECK macros in pairs, providing the
name of the task whose time will be measured. The name should be a single string of characters. It MUST NOT be in quotes.

Printing statistics is done using the PRINT_STATISTICS macro, providing the file name.
@attention The file name is in quotes, unlike other places where macros are called.

\code
#include PerformanceCheck.h

void FunctionToProfile()
{
	START_PERFORMANCE_CHECK(TASK_NAME)

// Here is the code whose performance we are measuring

	END_PERFORMANCE_CHECK(TASK_NAME)
}

\endcode

*/
class PerformanceCheck
{
private:
	std::vector<_PerformanceData>		m_samples;

public:
	PerformanceCheck() = default;
	~PerformanceCheck() = default;

	void				StartPerformanceCheck	( unsigned int index );
	void				EndPerformanceCheck		( unsigned int index );
	void				ClearSamples			();

	unsigned int		RegisterTaskName		( const char* taskName );

	void				PrintConsolePerformanceStatisticsAsync	();
	void				PrintPerformanceStatisticsAsync			( const std::string& outputFile );

private:
    static void         PrintToFile				( const std::string& outputFile, std::vector< _PerformanceData > data_copy );
	static void			PrintConsole			( std::vector<_PerformanceData> data_copy );
    static void			Print					( std::ostream& out, std::vector< _PerformanceData > data_copy );
};


#ifdef PERFORMANCE_CHECK

PerformanceCheck&		GetPerformanceCheck();

#define REGISTER_PERFORMANCE_CHECK( name ) static unsigned int __performance_task_id ## name = GetPerformanceCheck().RegisterTaskName( # name );

#define START_PERFORMANCE_CHECK( name )																	\
static unsigned int __performance_task_id ## name = GetPerformanceCheck().RegisterTaskName( # name );	\
GetPerformanceCheck().StartPerformanceCheck( __performance_task_id ## name );


#define END_PERFORMANCE_CHECK( name )	GetPerformanceCheck().EndPerformanceCheck( __performance_task_id ## name );
#define PRINT_STATISTICS( s )			GetPerformanceCheck().PrintPerformanceStatisticsAsync( s );
#define PRINT_STATISTICS_CONSOLE()		GetPerformanceCheck().PrintConsolePerformanceStatisticsAsync();
#define PERFORMACE_CHECK_CLEAR_SAMPLES	GetPerformanceCheck().ClearSamples();

#else

#define START_PERFORMANCE_CHECK( x )
#define END_PERFORMANCE_CHECK( x )
#define REGISTER_PERFORMANCE_CHECK( x )
#define PRINT_STATISTICS( s )
#define PRINT_STATISTICS_CONSOLE()
#define PERFORMACE_CHECK_CLEAR_SAMPLES 

#endif


}	// sw
