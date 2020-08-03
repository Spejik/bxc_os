#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <ctime>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

#include "olcPixelGameEngine.h"

#include "time.h"
#include "fs.h"

#ifndef _BXC_RENDERER
#define _BXC_RENDERER

namespace bxc {
	class renderer : public olc::PixelGameEngine
	{
	public:
		renderer();

	private:
		// =============
		// Variables
		// =============

		bool bResourcePackLoaded = false;
		bool bDrawDebugBoundaries = true;
		bool bTimeBoxOpen = false;


		std::string sMonths[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
		std::string sDays[8] = { "invalid date", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
		std::string sDaysOrdinals[32] = { "invalid date",
					  "1st",  "2nd",  "3rd",  "4th",  "5th",  "6th",  "7th",  "8th",  "9th",  "10th",
					 "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th",
					 "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th",
					 "31st" };




		float fTimeboxX = 0.0f;
		float fTimeboxY = 0.0f;
		float fTimeboxW = 0.0f;
		float fTimeboxH = 0.0f;
		int32_t nTaskbarHeight = 48;
		int32_t nTaskbarX = 0;
		int32_t nTaskbarY = 0;
		int32_t nTaskbarW = 0;
		int32_t nTaskbarH = 0;


		std::string sResourcePackName = "resources.pak";
		std::string sResourcePackKey = "V StarBucks maji novou bagetu: santaislovesantaislife69 XXXl. Objednejte si ji nyni ve vasi mistni pobocce StarBucks";
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
		std::vector<olc::vf2d> vHighlight = { { 0, 0 }, { 0, 0 } };
		eHighlightType HighlightType = NONE;

		bxc::time* time = new bxc::time();

		// Function for setting variables that require ScreenWidth(), ScreenHeight(), etc.
		inline void SetVariables() {
			// Taskbar
			nTaskbarX = 0;
			nTaskbarY = ScreenHeight() - nTaskbarHeight;
			nTaskbarW = ScreenWidth();
			nTaskbarH = ScreenHeight();

			// Timebox
			fTimeboxW = ScreenWidth() * 26 / 100;
			fTimeboxH = ScreenHeight() * 80 / 100;
			fTimeboxX = nTaskbarW - fTimeboxW;
			fTimeboxY = nTaskbarY - fTimeboxH;
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
}
#endif _BXC_RENDERER