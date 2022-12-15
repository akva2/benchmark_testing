#pragma once // Yes, I know about the core guidelines not recommending this
#include <config.hpp>

#if PROGRAM_USE_TRACY
#include "timers/tracy.hpp"
#elif PROGRAM_USE_EASY_PROFILER
#include "timers/easy.hpp"
#elif PROGRAM_USE_REMOTERY
#include "timers/remotery.hpp"
#else
#include "timers/none.hpp"
#endif
