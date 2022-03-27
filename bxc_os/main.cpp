#include "main.hpp"


struct window {
	int px;
	int py;
	int sx;
	int sy;
	std::string name;
};

bool Updater() {
	std::string response = "";
	spdlog::info("Update {} is available! Download it? [(y)es/(n)o] : ", Http::GetVersion());
	std::cin >> response;

	if (response.starts_with("y")) 
	{
		Http::GetUpdate();
		return true;
	}
	return false;
}


int main()
{
	Config::LoadConfig();

	// Window settings
	int width = 1280;
	int height = 720;
	int pixel = 1;
	bool useFullScreen = false;
	bool useVsync = false;
	
	// Tries to read config's fullscreen value, else uses ask
	int cfgFullscreen = Config::GetConfigIntField("fullscreen");

	// Asks user for fullscreen settings
	if (cfgFullscreen == (int)FULLSCREEN::ASK || cfgFullscreen == JSON_UNDEFINED_INT)
	{
		// Fullscreen prompt
		std::cout << "Run in fullscreen mode? [(y)es/(n)o/(a)lways/(ne)ver] : ";
		std::string fullscreen = "";
		std::cin >> fullscreen;

		if (fullscreen.starts_with("y"))
		{ 
			useFullScreen = true; 
		}
		else if (fullscreen.starts_with("ne"))
		{
			useFullScreen = false;
			Config::SetConfigIntField("fullscreen", (int)FULLSCREEN::NEVER);
		}
		else if (fullscreen.starts_with("n"))
		{
			useFullScreen = false;
		}
		else if (fullscreen.starts_with("a"))
		{
			useFullScreen = true;
			Config::SetConfigIntField("fullscreen", (int)FULLSCREEN::ALWAYS);
		}
		else
		{
			useFullScreen = false;
		}
	}
	else if (cfgFullscreen == (int)FULLSCREEN::ALWAYS)
		useFullScreen = true;
	else if (cfgFullscreen == (int)FULLSCREEN::NEVER)
		useFullScreen = false;
	else
	{
		spdlog::error("Invalid config.json value: fullscreen => {}", cfgFullscreen);
		std::cin.get(); 
		return 0;
	}

	// Gets screen dimensions, so the rendered image isn't stretched or something
	if (useFullScreen)
	{
		RECT rect;
		GetWindowRect(GetDesktopWindow(), &rect);
		width = rect.right;
		height = rect.bottom;
	}

	bRenderer os;
	if (os.Construct(width, height, pixel, pixel, useFullScreen, useVsync))
		os.Start();
	else
	{
		spdlog::critical("Couldn't construct BXC OS class :(");
		std::cin.get(); 
		return 0;
	}

	return 0;
}