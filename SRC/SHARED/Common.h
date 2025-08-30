#pragma once

#include <string>

#include "PlatformSpecific.h"
#include "Types.h"
#include "Macros.h"
#include "Logging.h"

extern const char* gBuildDate;
int GetBuildNum( const char* date );

struct EngineOptions
{
	bool CallQuit = false;
	u32 ScreenWidth = 640;
	u32 ScreenHeight = 480;

	std::string NetAddr = "localhost";
	std::string NetPort = "27015";

	bool RenderDemo = true; // Should we render dummy shit RN - APAMk2
} extern EngineOpts;

extern Logger* LogMngr;