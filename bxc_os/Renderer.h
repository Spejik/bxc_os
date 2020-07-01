#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <chrono>
#include <time.h>

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
	olc::vf2d vMouse = { 0, 0 };
	olc::vf2d vMouseOld = { 0,0 };


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
