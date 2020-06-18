#define OLC_PGE_APPLICATION

#include <iostream>
#include <ctime>
#include <chrono> 
#include "olcPixelGameEngine.h"
#include "json.hpp"
using namespace std;

struct window {
	int px;
	int py;
	int sx;
	int sy;
	string name;
};

class bxc_os : public olc::PixelGameEngine
{
public:
	bxc_os()
	{
		sAppName = "BXC OS";
	}

private: 
	string sResourcePackName = "./resources.bxc_pack";
	string sResourcePackKey = "V StarBucks maji novou bagetu: santaislovesantaislife69 XXXl. Objednejte si ji nyni ve vasi mistni pobocce StarBucks";

	olc::Sprite* sprBackground;
	olc::Sprite* sprLogo;
	olc::ResourcePack* RP = new olc::ResourcePack();

	uint32_t nLayerBackground = 1;
	uint32_t nLayerMain = 2;

public:
	bool OnUserCreate() override
	{
		//RP->AddFile("./assets/logo_tr_48.png");
		//RP->SavePack(sResourcePackName, sResourcePackKey);

		if (!RP->LoadPack(sResourcePackName, sResourcePackKey))
		{
			DrawString(4, 4, "FATAL ERROR: Loading " + sResourcePackName + " failed.", olc::RED, 2);
			DrawString(4, 28, "The file might be corrupted, or it doesn't exist.", olc::RED, 2);
		}


		sprBackground = new olc::Sprite("./assets/background.png", RP);
		sprLogo = new olc::Sprite("./assets/logo_w_48.png", RP);

		SetDrawTarget(nLayerBackground);
		Clear(olc::BLACK);
		DrawSprite(0, 0, sprBackground, 0.5, 0.5);
		EnableLayer(nLayerBackground, true);
		SetDrawTarget(nLayerMain);
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		map<int, int> mTaskbarLoc = { { 1, 0 }, { 2, ScreenHeight() - 48 }, { 3, ScreenWidth() }, { 4, ScreenHeight() } };
		// Gets system Time
		struct tm Tm;
		time_t Time = time(0);
		tm* TimeNow = localtime_s(&Time);

		int nYear = TimeNow->tm_year;
		int nMonth = TimeNow->tm_mon + 1;
		int nDay = TimeNow->tm_mday;
		int nHour = TimeNow->tm_hour;
		int nMin = TimeNow->tm_min;
		int nSec = TimeNow->tm_sec;

		// Creates the taskbar
		SetPixelMode(olc::Pixel::ALPHA);
		FillRect({ mTaskbarLoc[1], mTaskbarLoc[2] }, { mTaskbarLoc[3], mTaskbarLoc[4] }, olc::Pixel(20, 20, 30, 0.1));
		DrawLine({ mTaskbarLoc[1], mTaskbarLoc[2] }, { mTaskbarLoc[3], mTaskbarLoc[2] }, olc::BLACK);

		// Inserts logo
		DrawSprite({ mTaskbarLoc[1], mTaskbarLoc[2] }, sprLogo);

		// Draws Time & Date
		DrawString({ 0, 0 }, nHour + ":" + nMin, olc::WHITE, 1.5);
		DrawString({ 0, 10 }, to_string(nDay) + "." + to_string(nMonth) + "." + to_string(nYear), olc::WHITE, 1.5);

		SetPixelMode(olc::Pixel::NORMAL);

		return true;
	}
};


int main()
{
	bool bUseFullScreen = false;
	bool bUseVsync = false;

	bxc_os os;
	if (os.Construct(1280, 720, 1, 1, bUseFullScreen, bUseVsync))
		os.Start();
	else
		cout << "Constructing BXC OS failed" << endl;

	return 0;
}