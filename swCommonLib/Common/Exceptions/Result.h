#pragma once
/**
@file Result.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.

Real implementation of Result can be found in ResultImpl.h. We need this file
to include Convert.h, because ErrorAdapter uses Convert::ToString for enum types.
*/


#include "swCommonLib/Common/Exceptions/Result.h"
#include "swCommonLib/Common/Exceptions/Nullable.h"
#include "swCommonLib/Common/Converters/Convert.h"

