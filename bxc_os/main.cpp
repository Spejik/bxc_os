#define OLC_PGE_APPLICATION
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <chrono>
#include <time.h>

#include "RendererEngine.h"
#include "Utils.h"

using namespace std;
using namespace chrono;


struct window {
	int px;
	int py;
	int sx;
	int sy;
	string name;
};


string PromptFullscreen() {
	string sFullscreen = "";

	// Fullscreen prompt
	cout << "Run in fullscreen mode? [(y)es/no/(a)lways/(n)ever] ";
	cin >> sFullscreen;

	if (sFullscreen.rfind("y", 0) == 0)
		return "yes";
	else if (sFullscreen.rfind("a", 0))
		return "yes";
	else if (sFullscreen.rfind("n", 0))
		return "no";
	else
		return "no"
}


int main()
{
	// Initializes Utils class
	Utils* utils = new Utils();

	// Window settings
	int nWidth;
	int nHeight;
	int nPixel = 1;
	bool bUseFullScreen = false;
	bool bUseVsync = false;
	
	// Tries to read config value, else uses ask
	string sCfgFullscreen = "ask";
	sCfgFullscreen = utils->GetConfigStringField("fullscreen");

	// Asks user for fullscreen settings
	if (sCfgFullscreen == "ask")
	{
		string sFullscreen = PromptFullscreen();
		if (sFullscreen == "yes")
			bUseFullScreen = true;
		else if (sFullscreen == "no")
			bUseFullScreen = false;
		else
			throw new runtime_error("unknown fullscreen settings value: " + sFullscreen);
	}
	else if (sCfgFullscreen == "always")
		bUseFullScreen = true;
	else if (sCfgFullscreen == "never")
		bUseFullScreen = false;
	else
		throw new runtime_error("unknown config[fullscreen] value: " + sCfgFullscreen);

	

	cout << "create " << utils->CreateAppDataDirectory() << endl;
	cout << "get " << utils->GetConfigBoolField("fullscreen") << endl;

	
	if (bUseFullScreen)
	{
		cout << "Running in fullscreen mode" << endl;
		cout << " - Calculating screen dimensions & ratio" << endl;
		RECT rect;
		GetWindowRect(GetDesktopWindow(), &rect);

		nWidth = rect.right;
		nHeight = rect.bottom;
		int nRatio = utils->gcd(nWidth, nHeight);
		int nRatioW = nWidth / nRatio;
		int nRatioH = nHeight / nRatio;

		cout << "   - dimensions " << nWidth << "x" << nHeight << endl;
		cout << "   - gcd " << nRatio << endl;
		cout << "   - aspect " << nWidth / nRatio << ":" << nHeight / nRatio << endl;
	}
	else
	{
		// Sets default 
		cout << "Running in 1280x720 mode" << endl;
		nWidth = 1280;
		nHeight = 720;
	}

	RendererEngine os;
	if (os.Construct(nWidth, nHeight, nPixel, nPixel, bUseFullScreen, bUseVsync))
		os.Start();
	else
	{
		cout << endl
			<< "    o===================================o    " << endl
			<< "    |   Constructing BXC OS failed :(   |    " << endl
			<< "    o===================================o    " << endl;

		cin.get(); system("pause"); return 0;
	}

	return 0;
}