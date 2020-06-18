#define OLC_PGE_APPLICATION
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <chrono> 
#include <time.h>
#include "olcPixelGameEngine.h"
#include "json.hpp"
using namespace std;
using namespace chrono;

struct window {
	int px;
	int py;
	int sx;
	int sy;
	string name;
};

struct Circle {
	float x;
	float y;
	float radius;
	int id;
	milliseconds placed;
};

class bxc_os : public olc::PixelGameEngine
{
public:
	bxc_os()
	{
		sAppName = "BXC OS";
	}

private: 
	Circle* circles;
	int nLastCircle = 0;
	string sResourcePackName = "./resources.bxc_pack";
	string sResourcePackKey = "V StarBucks maji novou bagetu: santaislovesantaislife69 XXXl. Objednejte si ji nyni ve vasi mistni pobocce StarBucks";

	olc::Sprite* sprBackground;
	olc::Sprite* sprLogo;
	olc::ResourcePack* RP = new olc::ResourcePack();

	uint32_t nLayerBackground = 1;
	uint32_t nLayerMain = 0;

	// If n is under 10 (9, 8, 7, ...), returns 09, 08, 07, ...
	string PrependTime(int n) {
		string sNum = to_string(n);
		if (n < 10)
			return "0" + sNum;
		else
			return sNum;
	}

	milliseconds TimeMS() {
		return duration_cast<milliseconds>(
			system_clock::now().time_since_epoch());
	}

	float RandFloatRange(float min, float max)
	{
		return ((max - min) * ((float)rand() / RAND_MAX)) + min;
	}

public:
	bool OnUserCreate() override
	{
		circles = new Circle[ScreenWidth() + ScreenHeight()];
		//RP->AddFile("./assets/background.png");
		//RP->AddFile("./assets/logo_tr_48.png");
		//RP->AddFile("./assets/logo_tr_84.png");
		//RP->AddFile("./assets/logo_w_48.png");
		//RP->AddFile("./assets/logo_w_84.png");
		//RP->AddFile("./assets/logo_b_48.png");
		//RP->AddFile("./assets/logo_b_84.png");
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
		//DrawRect(0, 0, ScreenWidth(), ScreenHeight(), olc::VERY_DARK_BLUE);
		DrawSprite(0, 0, sprBackground, 0.5, 0.5);
		EnableLayer(nLayerBackground, true);
		SetDrawTarget(nLayerMain);
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		float fSourceX = GetMouseX();
		float fSourceY = GetMouseY();
		// Clears the screen, so we don't have any pixels overlapping
		Clear(olc::BLANK);

		// Taskbar Dimensions
		int nTaskbarHeight = 48;
		int nTaskbarX = 0;
		int nTaskbarY = ScreenHeight() - nTaskbarHeight;
		int nTaskbarW = ScreenWidth();
		int nTaskbarH = ScreenHeight();

		// Gets system Time
		time_t Time = time(0);
		tm* TimeNow = localtime(&Time);

		// Create time
		int nYear = TimeNow->tm_year + 1900;
		int nMonth = TimeNow->tm_mon + 1;
		int nDay = TimeNow->tm_mday;
		int nHour = TimeNow->tm_hour;
		int nMin = TimeNow->tm_min;
		int nSec = TimeNow->tm_sec;
		string sTime = PrependTime(nHour) + ":" + PrependTime(nMin) + ":" + PrependTime(nSec);
		string sDate = PrependTime(nDay) + "." + PrependTime(nMonth) + "." + PrependTime(nYear);

		// Creates the taskbar
		SetPixelMode(olc::Pixel::ALPHA);
		FillRect({ nTaskbarX, nTaskbarY }, { nTaskbarW, nTaskbarH }, olc::Pixel(20, 20, 30, 1));
		DrawLine({ nTaskbarX, nTaskbarY }, { nTaskbarW, nTaskbarY }, olc::WHITE);

		// Inserts logo
		DrawSprite({ nTaskbarX, nTaskbarY }, sprLogo);

		// Draws Time & Date
		DrawString({ nTaskbarW - 92, nTaskbarH - 36 }, sTime, olc::WHITE, 1.5);
		DrawString({ nTaskbarW - 100, nTaskbarH - 24 }, sDate, olc::WHITE, 1.5);

		SetPixelMode(olc::Pixel::NORMAL);

		if (GetMouse(0).bPressed)
		{
			nLastCircle++;
			int id = nLastCircle;
			circles[id].x = fSourceX;
			circles[id].y = fSourceY;
			circles[id].placed = TimeMS();
			circles[id].radius = RandFloatRange(0.5f, 3.5f);
			circles[id].id = id;
			cout << "[" << circles[id].placed.count() << "] New circle @ " << fSourceX << "-" << fSourceY
				 << " with the radius of " << circles[id].radius
				 << " and ID " << id << endl;
		}

		for (int i = 1; i <= nLastCircle; i++)
		{
			if (TimeMS().count() - circles[i].placed.count() < 3000)
				DrawCircle(circles[i].x, circles[i].y, (circles[i].radius) * 20, olc::WHITE);
		}


		return true;
	}
};


int main()
{
	int nBonusSize = 280;
	int nWidth = 1280 + nBonusSize;
	int nHeight = 720 + nBonusSize;
	int nPixel = 1;
	bool bUseFullScreen = false;
	bool bUseVsync = false;
	

	bxc_os os;
	if (os.Construct(nWidth, nHeight, nPixel, nPixel, bUseFullScreen, bUseVsync))
		os.Start();
	else
		cout << endl
		     << "    o===================================o    " << endl
		     << "    |   Constructing BXC OS failed :(   |    " << endl
		     << "    o===================================o    " << endl;

	cin.get(); system("pause"); return 0;
}