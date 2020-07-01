#define OLC_PGE_APPLICATION
#define _CRT_SECURE_NO_WARNINGS
#define _VERSION 0.9
#define ASK 1
#define ALWAYS 2
#define NEVER 3

#include <iostream>
#include <string>

#include "Renderer.h"
#include "Utils.h"
#include "http.h"

using namespace std;


struct window {
	int px;
	int py;
	int sx;
	int sy;
	string name;
};


int main()
{
	// Initializes and connects to Database
	Http* http = new Http();
	http->GetVersion();

	// Initializes Utils class
	Utils* utils = new Utils();
	utils->LoadConfig();

	// Window settings
	int nWidth = 1280;
	int nHeight = 720;
	int nPixel = 1;
	bool bUseFullScreen = false;
	bool bUseVsync = false;
	
	// Tries to read config's fullscreen value, else uses ask
	int sCfgFullscreen = utils->GetConfigIntField("fullscreen");

	// Asks user for fullscreen settings
	if (sCfgFullscreen == ASK || sCfgFullscreen == UNDEFINED_INT)
	{
		string sFullscreen = "";

		// Fullscreen prompt
		cout << "Run in fullscreen mode? [(y)es/(n)o/(a)lways/(ne)ver] : ";
		cin >> sFullscreen;

		if (sFullscreen.rfind("y", 0) == 0)
			bUseFullScreen = true;
		// "never" must be before "no", so that it doesn't think user said "no", because of "n" :weSmart:
		else if (sFullscreen.rfind("ne", 0) == 0) 
		{
			bUseFullScreen = false;
			utils->SetConfigIntField("fullscreen", NEVER);
		}
		else if (sFullscreen.rfind("n", 0) == 0) 
			bUseFullScreen = false;
		else if (sFullscreen.rfind("a", 0) == 0) {
			bUseFullScreen = true;
			utils->SetConfigIntField("fullscreen", ALWAYS);
		} 
		else
			bUseFullScreen = false;
	}
	else if (sCfgFullscreen == ALWAYS)
		bUseFullScreen = true;
	else if (sCfgFullscreen == NEVER)
		bUseFullScreen = false;
	else
		bUseFullScreen = false;


	// Gets screen dimensions, so the image isn't stretched or anything like that
	if (bUseFullScreen)
	{
		RECT rect;
		GetWindowRect(GetDesktopWindow(), &rect);
		nWidth = rect.right;
		nHeight = rect.bottom;
	}

	Renderer os;
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