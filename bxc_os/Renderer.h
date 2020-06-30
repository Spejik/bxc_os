#pragma once

#include <iostream>
#include <chrono>

#include "olcPixelGameEngine.h"

using namespace std;
using namespace chrono;

class Renderer : public olc::PixelGameEngine
{
public:
	Renderer();

private:
	// =============
	// Variables
	// =============

	bool bResourcePackLoaded = false;

	int nTaskbarHeight = 48;
	int nTaskbarX = 0;
	int nTaskbarY = ScreenHeight() - nTaskbarHeight;
	int nTaskbarW = ScreenWidth();
	int nTaskbarH = ScreenHeight();

	string sResourcePackName = "./resources.bxcpack";
	string sResourcePackKey = "V StarBucks maji novou bagetu: santaislovesantaislife69 XXXl. Objednejte si ji nyni ve vasi mistni pobocce StarBucks";
	olc::Sprite* sprBackground;
	olc::Sprite* sprLogo;
	olc::Decal* decBackground;
	olc::Decal* decLogo;
	olc::ResourcePack* RP = new olc::ResourcePack();


	// If time has 1 decimal place, prepends it with a 0
	string PrependTime(int n);
	milliseconds TimeMS();
	float RandFloatRange(float min, float max);
	void PackageResourcePack();
	bool IsPointInRect(olc::vf2d point, olc::vf2d start, olc::vf2d end);

public:
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);
};
