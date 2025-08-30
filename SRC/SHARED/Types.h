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

template<typename T> struct Vector3
{
	T x;
	T y;
	T z;
};

typedef Vector3<i32> Vector3i;
typedef Vector3<float> Vector3f;

struct Rect
{
	u32 x = 0; // X coord
	u32 y = 0; // Y coord
	u32 w = 0; // Width
	u32 h = 0; // Height
};