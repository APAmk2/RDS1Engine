#include "Common.h"

const char* gBuildDate = __DATE__;

EngineOptions EngineOpts;
Logger* LogMngr = nullptr;

static const char* const mon[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
static const char mond[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int GetBuildNum(const char* date)
{
	int b;
	int m = 0;
	int d = 0;
	int y = 0;

	for (m = 0; m < 11; m++)
	{
		if (!_strnicmp(&date[0], mon[m], 3))
			break;
		d += mond[m];
	}

	d += atoi(&date[4]) - 1;
	y = atoi(&date[7]) - 1900;
	b = d + (int)((y - 1) * 365.25f);

	if (((y % 4) == 0) && m > 1)
		b += 1;
	b -= 45502; // Jul 31 2025

	return b;
}