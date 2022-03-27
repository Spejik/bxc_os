#pragma once

#include <iostream>
#include <string>

#include "olcPixelGameEngine.h"


class bWindow
{
public: 
	bWindow(olc::vf2d position, olc::vf2d scale, std::string code);

private:
	olc::vf2d position = { 50, 50 };
	olc::vf2d scale = { 250, 300 };
	const std::string code = "";

public:
	bool Render(olc::PixelGameEngine* pge);
};
