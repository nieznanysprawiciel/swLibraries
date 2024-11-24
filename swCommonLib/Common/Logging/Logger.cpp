/**
@file Logger.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swCommonLib/Common/Logging/Logger.h"

namespace sw
{
std::unique_ptr < ILogger > ILogger::s_logger = std::make_unique< NullLogger >();


// ================================ //

ILogger&         ILogger::Logger()
{
    if( !s_logger )
        ILogger::s_logger = std::make_unique< NullLogger >();
    return *ILogger::s_logger;
}


}	// sw

