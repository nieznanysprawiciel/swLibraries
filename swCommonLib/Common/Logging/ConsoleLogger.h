#pragma once
/**
@file ConsoleLogger.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <chrono>

#include "Logger.h"

#include "swCommonLib/Common/fmt.h"


namespace sw
{

/**@brief Logger that writes messages to console.
@ingroup Logging*/
class ConsoleLogger : public ILogger
{
public:
    ConsoleLogger() = default;
    ~ConsoleLogger() = default;


    void        Log     ( LogLevel level, const char* messagee );
};

// ================================ //

void        ConsoleLogger::Log( LogLevel level, const char* message )
{
    using std::chrono::system_clock;
    using std::chrono::time_point;
    time_point< system_clock > timestamp = system_clock::now();
    fmt::println( "{} [{:%Y-%m-%d %H:%M:%S}] {}", LogLevelToString( level ), timestamp, message );
}

}  // sw
