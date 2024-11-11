/**
@file PerformanceCheck.cpp
@brief This file is part of the graphic engine SWEngine.
*/

#include "PerformanceCheck.h"

#include <future>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

///<@todo Don't use windows.h here. Build platform specific libraries.
#include <Windows.h>

#undef min
#undef max
#undef CreateDirectory

#include "swCommonLib/Common/MemoryLeaks.h"
#include "swCommonLib/System/Path.h"
#include "swCommonLib/System/Dir.h"


namespace sw
{

PerformanceCheck& GetPerformanceCheck()
{
	static PerformanceCheck performanceCheck;
	return performanceCheck;
}

const int floatPrintPrecision = 8; ///< Number of decimal places to be displayed for floats.

/**@brief Function called at the beginning of task execution. Saves the current time.

@param[in] index Index of the task in the m_samples array.*/
void PerformanceCheck::StartPerformanceCheck(unsigned int index)
{
	if (index < m_samples.size())
	{
		_LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		m_samples[index].LastStartTime = currentTime.QuadPart;
	}
}

/**@brief Function called at the end of task execution. Updates all statistics.

@param[in] index Index of the task in the m_samples array.*/
void PerformanceCheck::EndPerformanceCheck(unsigned int index)
{
	if (index < m_samples.size())
	{
		_LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		uint64 timeSpent = currentTime.QuadPart - m_samples[index].LastStartTime;
		m_samples[index].WholeTime += timeSpent;

		if (timeSpent > m_samples[index].MaxTime)
			m_samples[index].MaxTime = timeSpent;
		if (timeSpent < m_samples[index].MinTime)
			m_samples[index].MinTime = timeSpent;

		m_samples[index].NumExecutions++;
	}
}

/**@brief Registers the task name for performance measurement.

@param[in] taskName Name of the task
@return Returns the task identifier, which can be used later to refer to the time measuring functions.*/
unsigned int PerformanceCheck::RegisterTaskName(const char* taskName)
{
	_PerformanceData newTask;
	newTask.TaskName = taskName;
	newTask.MaxTime = 0;
	newTask.MinTime = std::numeric_limits<uint32>::max();
	newTask.NumExecutions = 0;
	newTask.WholeTime = 0;

	m_samples.push_back(newTask);
	return (unsigned int)(m_samples.size() - 1);
}

void PerformanceCheck::PrintConsolePerformanceStatisticsAsync()
{
	std::future< void > printAsync = std::async( PrintConsole, m_samples );
}

/**@brief Asynchronously prints statistics to the specified file.

Since the statistics are saved in a separate thread, too frequent calls to this function may cause them to overlap.

@param[in] outputFile File to which the statistics should be written.*/
void PerformanceCheck::PrintPerformanceStatisticsAsync(const std::string& outputFile)
{
    std::future< void > printAsync = std::async( PrintToFile, outputFile, m_samples );
}

/**@brief Actual printing function.*/
void PerformanceCheck::PrintToFile(const std::string& outputFile, std::vector<_PerformanceData> data_copy)
{
    filesystem::Dir::CreateDirectory( ( filesystem::Path::WorkingDirectory() / outputFile ) );

	std::fstream output;
	output.open(outputFile.c_str(), std::fstream::out | std::fstream::app);
	if (!output.good())
		return;

	Print( output, data_copy );

	output.close();
}

// ================================ //

void PerformanceCheck::PrintConsole( std::vector< _PerformanceData > data_copy )
{
    Print( std::cout, data_copy );
}

// ================================ //

void PerformanceCheck::Print( std::ostream& output, std::vector< _PerformanceData > data_copy )
{
    LARGE_INTEGER counterFreq;
    QueryPerformanceFrequency( &counterFreq );

	const auto dataWidth = 16;
    const auto recordWidth = 32;

	output << std::left;
	output << std::setw( recordWidth ) << "Performance test:";
    output << std::setw( dataWidth ) << "Average (ms)";
    output << std::setw( dataWidth ) << "Minimum (ms)";
    output << std::setw( dataWidth ) << "Maximum (ms)";
    output << std::setw( dataWidth ) << "Whole Time (ms)";
    output << std::setw( dataWidth ) << "Num executions";
    output << std::endl;
	

	for (auto taskData : data_copy)
	{
        output.width( recordWidth );
		output << std::left;
		output << taskData.TaskName;
		output.width(0);
		output << std::fixed;
		output << std::setw(dataWidth)<< std::setprecision(floatPrintPrecision) << 1000 * taskData.WholeTime / double(taskData.NumExecutions * counterFreq.QuadPart);
		output << std::setw(dataWidth) << std::setprecision(floatPrintPrecision) << 1000 * taskData.MinTime / double(counterFreq.QuadPart);
		output << std::setw(dataWidth) << std::setprecision(floatPrintPrecision) << 1000 * taskData.MaxTime / double(counterFreq.QuadPart);
		output << std::setw(dataWidth) << std::setprecision(floatPrintPrecision) << 1000 * taskData.WholeTime / double(counterFreq.QuadPart);
		output << taskData.NumExecutions << std::endl;
	}
	output << std::endl;
}

// ================================ //

void PerformanceCheck::ClearSamples()
{
	for (auto& sample : m_samples)
	{
		sample.MaxTime = 0;
		sample.MinTime = std::numeric_limits<uint32>::max();
		sample.WholeTime = 0;
		sample.NumExecutions = 0;
	}
}

} // namespace sw
