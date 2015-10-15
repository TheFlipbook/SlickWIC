#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <tchar.h>

// WIC
#include <wincodec.h>
#include <wincodecsdk.h>

// DevIL
#include <IL/il.h>
#include <IL/ilu.h>

// STD
#include <iostream>

// Internal
// DLL Include Guard
#ifdef SLICKWIC_EXPORTS
	#define SLICKWIC_API __declspec(dllexport)
#else
	#define SLICKWIC_API __declspec(dllimport)
#endif

#include "IUnknownImpl.h"