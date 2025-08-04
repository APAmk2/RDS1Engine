#pragma once

typedef char i8;
typedef short i16;
typedef int i32;
typedef long int i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long int u64;

struct ColorRGB
{
	u8 r = 0;
	u8 g = 0;
	u8 b = 0;
};

struct ColorRGBA
{
	u8 r = 0;
	u8 g = 0;
	u8 b = 0;
	u8 a = 0;
};

struct Vertex
{
	float points[3];
};

constexpr char ENGINE_NAME[] = "RDS1 Engine";

struct EngineOptions
{
	bool CallQuit = false;
	u32 ScreenWidth = 1024;
	u32 ScreenHeight = 768;

	float CamX = 1.0f;
	float CamY = 1.0f;
	float CamZ = 1.0f;

	bool RenderDemo = true; // Should we render dummy shit RN - APAMk2
} extern EngineOpts;