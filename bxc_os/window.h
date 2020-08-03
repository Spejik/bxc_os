#pragma once

#include <iostream>
#include <string>
#include <boost/python.hpp>

#include "olcPixelGameEngine.h"

#ifndef _BXC_WINDOW
#define _BXC_WINDOW

namespace bxc {
	class window
	{
	public: 
		window(olc::vf2d position, olc::vf2d scale, std::string code);

	private:
		olc::vf2d vPosition = { 50, 50 };
		olc::vf2d vScale = { 250, 300 };
		std::string sCode = "";

	public:
		bool Draw(olc::PixelGameEngine* pge);
	};
}
#endif // !_BXC_WINDOW

