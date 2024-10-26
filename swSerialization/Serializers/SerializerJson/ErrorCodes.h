#pragma once
/**
@file ErrorCodes.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#include <rapidjson/error/error.h>

const char* GetStringFromCode( rapidjson::ParseErrorCode code );