#pragma once

#include "Time.hpp"
#include "Filesystem.hpp"

#include "olcPixelGameEngine.h"

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <string>
#include <filesystem>
#include <ctime>
#include <random>


class bRenderer : public olc::PixelGameEngine
{
public:
	bRenderer();

private:
	// =============
	// Variables
	// =============

	bool resourcePackLoaded = false;
	bool drawDebugBoundaries = true;
	bool timeBoxOpen = false;

	std::random_device rd;

	std::string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	std::string days[8] = { "invalid date", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
	std::string daysOrdinals[32] = { "invalid date",
				  "1st",  "2nd",  "3rd",  "4th",  "5th",  "6th",  "7th",  "8th",  "9th",  "10th",
				 "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th",
				 "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th",
				 "31st" };


	float timeboxX = 0.0f;
	float timeboxY = 0.0f;
	float timeboxW = 0.0f;
	float timeboxH = 0.0f;
	int32_t taskbarHeight = 48;
	int32_t taskbarX = 0;
	int32_t taskbarY = 0;
	int32_t taskbarW = 0;
	int32_t taskbarH = 0;

	std::string resourcePackName = "resources.pak";
	std::string resourcePackKey = "V StarBucks maji novou bagetu: santaislovesantaislife69 XXXl. Objednejte si ji nyni ve vasi mistni pobocce StarBucks";
	olc::Sprite* sprBackground;
	olc::Sprite* sprLogo;
	olc::Decal* decBackground;
	olc::Decal* decLogo;
	olc::ResourcePack* RP = new olc::ResourcePack();
	uint32_t LayerBg;
	uint32_t LayerUi;
	olc::vf2d vMouse = { 0, 0 };
	olc::vf2d vMouseOld = { 0,0 };

	enum eHighlightType {
		NONE, HOVER, CLICK
	};
	std::vector<olc::vf2d> highlight = { { 0, 0 }, { 0, 0 } };
	eHighlightType HighlightType = NONE;

	// Function for setting variables that require ScreenWidth(), ScreenHeight(), etc.
	inline void SetVariables() {
		// Taskbar
		taskbarX = 0;
		taskbarY = ScreenHeight() - taskbarHeight;
		taskbarW = ScreenWidth();
		taskbarH = ScreenHeight();

		// Timebox
		timeboxW = ScreenWidth() * 26 / 100;
		timeboxH = ScreenHeight() * 80 / 100;
		timeboxX = taskbarW - timeboxW;
		timeboxY = taskbarY - timeboxH;
	}


	// Generates random float between two numbers
	float RandFloatRange(float min, float max);
	// Packages all files in the directory assets into one file, resources.pak
	void PackageResourcePack();
	// Calculates if a 2D point is within the boundaries of a rectangle
	bool isPointInRect(olc::vf2d point, olc::vf2d start, olc::vf2d end);
	// Sets app name
	void SetAppName(std::string name);
	// Draw a highlight on a certain area
	void SetHighlight(olc::vf2d start, olc::vf2d end);
	void UnsetHighlight();
	void SetHighlightType(eHighlightType type);

public:
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);
};
