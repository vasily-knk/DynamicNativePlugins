#pragma once

#include "simlabs_config.h"

#include "common/stl.h"
#include "common/boost.h"

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
// Windows Header Files:
#include <windows.h>

#include <IUnityInterface.h>
#include <IUnityGraphics.h>

#include "logger/logger.hpp"

#include "reflection/proc/dict_refl.h"
#include "info_io/info_io.h"

#include "common/points.h"
#include "common/performance_counter.h"
#include "common/unicode_support.h"