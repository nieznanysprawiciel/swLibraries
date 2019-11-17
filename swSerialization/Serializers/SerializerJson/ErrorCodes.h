#pragma once
/**
@file ErrorCodes.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/


#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <rapidjson/error/error.h>

const char* GetStringFromCode( rapidjson::ParseErrorCode code );
