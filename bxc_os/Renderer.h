#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <filesystem>
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


	string sAppdata = getenv("APPDATA");
	string sAppdataDirectory = sAppdata + "\\bxc_os\\";
	string sResourcePackName = sAppdataDirectory + "resources.pak";
	string sResourcePackKey = "V StarBucks maji novou bagetu: santaislovesantaislife69 XXXl. Objednejte si ji nyni ve vasi mistni pobocce StarBucks";
	olc::Sprite* sprBackground;
	olc::Sprite* sprLogo;
	olc::Decal* decBackground;
	olc::Decal* decLogo;
	olc::ResourcePack* RP = new olc::ResourcePack();
	uint32_t LayerBg;
	uint32_t LayerUi;
	olc::vf2d vMouse = { 0, 0 };
	olc::vf2d vMouseOld = { 0,0 };


	// If time has 1 decimal place, prepends it with a 0
	string PrependTime(int n);
	// Gets current time in milliseconds
	milliseconds TimeMS();
	// Generates random float between two numbers
	float RandFloatRange(float min, float max);
	// Packages all files in the directory assets into one file, resources.pak
	void PackageResourcePack();
	// Calculates if a 2D point is within the boundaries of a rectangle
	bool IsPointInRect(olc::vf2d point, olc::vf2d start, olc::vf2d end);

public:
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);
};
