#pragma once

#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include <rapidjson/error/error.h>

const char* GetStringFromCode( rapidjson::ParseErrorCode code );
