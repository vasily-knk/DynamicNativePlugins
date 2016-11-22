// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>



#include <fstream>

#include <memory>
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;

#include <map>

#include <string>
using std::string;

#include <cstdint>
#include <algorithm>