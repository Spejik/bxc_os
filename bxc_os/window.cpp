#include "Window.hpp"

bWindow::bWindow(olc::vf2d position, olc::vf2d scale, std::string code)
	: position(position)
	, scale(scale)
	, code(code)
{
}

bool bWindow::Render(olc::PixelGameEngine* pge)
{
	pge->DrawRect(position, scale, olc::DARK_GREY);
	return true;
}