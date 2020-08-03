#include "window.h"

bxc::window::window(olc::vf2d position, olc::vf2d scale, std::string code)
{
	vPosition = position;
	vScale = scale;
	sCode = code;
}

bool bxc::window::Draw(olc::PixelGameEngine* pge)
{
	return true;
}