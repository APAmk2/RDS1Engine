#pragma once

#include <vector>

#include "../Common.h"

class Texture
{
public:
	std::vector<ColorRGB>* PixelData = NULL;
	u32 Width = 0;
	u32 Height = 0;

	Texture(std::vector<ColorRGB>* data, u32 w, u32 h);
	~Texture();
};