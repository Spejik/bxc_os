
#ifndef OLC_PGE_APPLICATION
#define OLC_PGE_APPLICATION
#endif

#ifndef APP_VERSION
#define APP_VERSION "0.18"
#endif
#ifndef FULLSCREEN_ASK
#define FULLSCREEN_ASK 1
#endif
#ifndef FULLSCREEN_ALWAYS
#define FULLSCREEN_ALWAYS 2
#endif
#ifndef FULLSCREEN_NEVER
#define FULLSCREEN_NEVER 3
#endif


#include "Renderer.h"
#include "Utils.h"
#include "http.h"


struct window {
	int px;
	int py;
	int sx;
	int sy;
	string name;
};

void Updater(Http* http) {
	string sDownload = "";
	cout << "There is an update (" << http->GetVersion() << ") available! Download it? [(y)es/(n)o] : ";
	cin >> sDownload;

	if (sDownload.rfind("y", 0) == 0) 
	{
		float nUpdated = http->GetUpdate();
		cout << "Installed BXC OS v" + http->GetVersion() << " in " << nUpdated / 1000 << "s. Please, close this window and run it again." << endl << endl;
		cin.get(); return;
	}
	if (sDownload.rfind("n", 0) == 0)
		exit(0);
}


int main()
{
	Http* http = new Http();
	if (http->GetVersion() != APP_VERSION)
		Updater(http);

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
	if (sCfgFullscreen == FULLSCREEN_ASK || sCfgFullscreen == JSON_UNDEFINED_INT)
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
			utils->SetConfigIntField("fullscreen", FULLSCREEN_NEVER);
		}
		else if (sFullscreen.rfind("n", 0) == 0) 
			bUseFullScreen = false;
		else if (sFullscreen.rfind("a", 0) == 0) {
			bUseFullScreen = true;
			utils->SetConfigIntField("fullscreen", FULLSCREEN_ALWAYS);
		} 
		else
			bUseFullScreen = false;
	}
	else if (sCfgFullscreen == FULLSCREEN_ALWAYS)
		bUseFullScreen = true;
	else if (sCfgFullscreen == FULLSCREEN_NEVER)
		bUseFullScreen = false;
	else
	{
		cout << "Invalid config.json value: fullscreen > " << sCfgFullscreen << endl;
		cin.get(); return 0;
	}


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

		cin.get(); return 0;
	}

	return 0;
}