#include "main.hpp"


struct window {
	int px;
	int py;
	int sx;
	int sy;
	std::string name;
};

int Updater(Http* http) {
	std::string sDownload = "";
	std::cout << "There is an update (" << http->GetVersion() << ") available! Download it? [(y)es/(n)o] : ";
	std::cin >> sDownload;

	if (sDownload.rfind("y", 0) == 0) 
	{
		http->GetUpdate();
		return 42;
	}
	if (sDownload.rfind("n", 0) == 0)
		return 0;
}


int main()
{
	Http* http = new Http();
	if (http->GetVersion() != APP_VERSION)
		return Updater(http);

	// Initializes class Utils
	bxc::Utils* utils = new bxc::Utils();

	// Window settings
	int nWidth = 1280;
	int nHeight = 720;
	int nPixel = 1;
	bool bUseFullScreen = false;
	bool bUseVsync = false;
	
	// Tries to read config's fullscreen value, else uses ask
	int sCfgFullscreen = utils->GetConfigIntField("fullscreen");

	// Asks user for fullscreen settings
	if (sCfgFullscreen == FULLSCREEN_ASK || sCfgFullscreen == JSON_UNDEFINED_INT)
	{
		// Fullscreen prompt
		std::cout << "Run in fullscreen mode? [(y)es/(n)o/(a)lways/(ne)ver] : ";
		std::string sFullscreen = "";
		std::cin >> sFullscreen;



		if (sFullscreen.rfind("y", 0) == 0)
		{ 
			bUseFullScreen = true; 
		}
		else if (sFullscreen.rfind("ne", 0) == 0)
		{
			bUseFullScreen = false;
			utils->SetConfigIntField("fullscreen", FULLSCREEN_NEVER);
		}
		else if (sFullscreen.rfind("n", 0) == 0)
		{
			bUseFullScreen = false;
		}
		else if (sFullscreen.rfind("a", 0) == 0)
		{
			bUseFullScreen = true;
			utils->SetConfigIntField("fullscreen", FULLSCREEN_ALWAYS);
		}
		else
		{
			bUseFullScreen = false;
		}
	}
	else if (sCfgFullscreen == FULLSCREEN_ALWAYS)
		bUseFullScreen = true;
	else if (sCfgFullscreen == FULLSCREEN_NEVER)
		bUseFullScreen = false;
	else
	{
		std::cout << "Invalid config.json value: fullscreen > " << sCfgFullscreen <<  std::endl;
		std::cin.get(); return 0;
	}


	// Gets screen dimensions, so the rendered image isn't stretched or something
	if (bUseFullScreen)
	{
		RECT rect;
		GetWindowRect(GetDesktopWindow(), &rect);
		nWidth = rect.right;
		nHeight = rect.bottom;
	}

	bxc::renderer os;
	if (os.Construct(nWidth, nHeight, nPixel, nPixel, bUseFullScreen, bUseVsync))
		os.Start();
	else
	{
		std::cout <<  std::endl
			<< "    o===================================o    " <<  std::endl
			<< "    |   Constructing BXC OS failed :(   |    " <<  std::endl
			<< "    o===================================o    " <<  std::endl;

		std::cin.get(); return 0;
	}

	return 0;
}