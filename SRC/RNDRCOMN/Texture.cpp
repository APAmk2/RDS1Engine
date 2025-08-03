#include "Texture.h"

Texture::Texture(std::vector<ColorRGB>* data, u32 w, u32 h)
{
	PixelData = data;
	Width = w;
	Height = h;
}
Texture::~Texture()
{

}