#pragma once
/**
@file Logger.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include <string>
#include <memory>

#include "swCommonLib/Common/TypesDefinitions.h"

namespace sw
{

/**@brief Logging levels.
@ingroup Logging*/
enum class LogLevel
{
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

class NullLogger;
class ILogger;
DEFINE_UPTR_TYPE( ILogger );


/**@brief This class is interface to write logger independent system.

Use your favourite logger internally.
@ingroup Logging*/
class ILogger
{
protected:
    static std::unique_ptr< ILogger > s_logger;

public:
    explicit ILogger() = default;
    virtual ~ILogger() = 0 {};


	void    Trace       ( const std::string& message ) { Log( LogLevel::Trace, message.c_str() ); }
    void    Debug       ( const std::string& message ) { Log( LogLevel::Debug, message.c_str() ); }
    void    Info        ( const std::string& message ) { Log( LogLevel::Info, message.c_str() ); }
    void    Warning     ( const std::string& message ) { Log( LogLevel::Warning, message.c_str() ); }
    void    Error       ( const std::string& message ) { Log( LogLevel::Error, message.c_str() ); }
    void    Critical    ( const std::string& message ) { Log( LogLevel::Critical, message.c_str() ); }

	void    Trace       ( const char* message ) { Log( LogLevel::Trace, message ); }
    void    Debug       ( const char* message ) { Log( LogLevel::Debug, message ); }
    void    Info        ( const char* message ) { Log( LogLevel::Info, message ); }
    void    Warning     ( const char* message ) { Log( LogLevel::Warning, message ); }
    void    Error       ( const char* message ) { Log( LogLevel::Error, message ); }
    void    Critical    ( const char* message ) { Log( LogLevel::Critical, message ); }

    virtual void    Log         ( LogLevel level, const char* message ) = 0;
    void            Log         ( LogLevel level, const std::string& message ) { Log( level, message.c_str() ); }

public:

    static void     SetLogger( std::unique_ptr< ILogger > logger ) { s_logger = std::move( logger ); }
    static ILogger& Logger();
};


/**@brief Logger for discarding on logs.
@ingroup Logging*/
class NullLogger : public ILogger
{
private:
protected:
public:
    NullLogger() = default;
    ~NullLogger() = default;

    void    Log( LogLevel level, const char* message ) override {}
};

// ================================ //

inline const char* LogLevelToString( LogLevel level )
{
    switch( level )
    {
        case LogLevel::Trace:
            return "Trace";
        case LogLevel::Debug:
            return "Debug";
        case LogLevel::Info:
            return "Info";
        case LogLevel::Warning:
            return "Warning";
        case LogLevel::Error:
            return "Error";
        case LogLevel::Critical:
            return "Critical";
        default:
            return "Undefined";
    }
}

#define LOG_MESSAGE( LEVEL, MESSAGE ) sw::ILogger::Logger().Log( LEVEL, MESSAGE );

#define LOG_TRACE( MESSAGE ) LOG_MESSAGE( sw::LogLevel::Trace, MESSAGE )
#define LOG_DEBUG( MESSAGE ) LOG_MESSAGE( sw::LogLevel::Debug, MESSAGE )
#define LOG_INFO( MESSAGE ) LOG_MESSAGE( sw::LogLevel::Info, MESSAGE )
#define LOG_WARN( MESSAGE ) LOG_MESSAGE( sw::LogLevel::Warning, MESSAGE )
#define LOG_ERROR( MESSAGE ) LOG_MESSAGE( sw::LogLevel::Error, MESSAGE )
#define LOG_CRITICAL( MESSAGE ) LOG_MESSAGE( sw::LogLevel::Critical, MESSAGE )


}	// sw

