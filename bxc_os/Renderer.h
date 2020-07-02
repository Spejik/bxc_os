#pragma once


#include <iostream>
#include <string>
#include <filesystem>
#include <ctime>
#include <chrono>
#include <time.h>
#include <boost/date_time.hpp>

#include "olcPixelGameEngine.h"

using namespace std;
using namespace std::chrono;



class Renderer : public olc::PixelGameEngine
{
public:
	Renderer();

private:
	// =============
	// Variables
	// =============

	bool bResourcePackLoaded = false;
	bool bDrawDebugBoundaries = true;
	bool bTimeBoxOpen = false;

	int32_t nTaskbarHeight = 48;
	int32_t nTaskbarX = 0;
	int32_t nTaskbarY = 0;
	int32_t nTaskbarW = 0;
	int32_t nTaskbarH = 0;


	/*string sAppdata = getenv("APPDATA");
	string sAppdataDirectory = sAppdata + "\\bxc_os\\";
	string sResourcePackName = sAppdataDirectory + "resources.pak";*/
	string sResourcePackName = "resources.pak";
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
	int nTimeMs();
	// Gets current time in microseconds
	int nTimeUs();
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
