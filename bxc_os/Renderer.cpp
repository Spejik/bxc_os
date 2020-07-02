#include "Renderer.h"


Renderer::Renderer()
{
	sAppName = "BXC OS";
}


// =============
// Private functions
// =============

string Renderer::PrependTime(int n)
{
	string sNum = to_string(n);
	if (n < 10)
		return "0" + sNum;
	else
		return sNum;
}

int Renderer::nTimeMs()
{
	return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

int Renderer::nTimeUs()
{
	return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
}

float Renderer::RandFloatRange(float min, float max)
{
	return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void Renderer::PackageResourcePack()
{
	string sAssetsPath = "assets/";

	for (const auto & entry : filesystem::recursive_directory_iterator(sAssetsPath))
	{
		// Ignore plain directories
		if (entry.is_directory())
			continue;

		// Ignore svg files, as they're the source files for most assets... and don't get encrypted
		if (entry.path().extension().string() == ".svg")
			continue;

		RP->AddFile(entry.path().string());
	}
	RP->SavePack(sResourcePackName, sResourcePackKey);
}


bool Renderer::IsPointInRect(olc::vf2d point, olc::vf2d start, olc::vf2d end) {
	bool inX = (point.x > start.x && point.x < end.x);
	bool inY = (point.y > start.y && point.y < end.y);
	
	return (inX && inY);
}


bool Renderer::OnUserCreate()
{
	PackageResourcePack();

	// Loads Resource Pack
	if (RP->LoadPack(sResourcePackName, sResourcePackKey))
		bResourcePackLoaded = true;
	else
		return true;

	// Set correct values to taskbar dimensions
	nTaskbarX = 0.0f;
	nTaskbarY = ScreenHeight() - nTaskbarHeight;
	nTaskbarW = ScreenWidth();
	nTaskbarH = ScreenHeight();

	// Loads assets
	sprBackground = new olc::Sprite("assets/background.png", RP);
	sprLogo = new olc::Sprite("assets/logo_white.png", RP);
	// Converts asset sprites to decals
	decBackground = new olc::Decal(sprBackground);
	decLogo = new olc::Decal(sprLogo);

	// Create and enable layers
	LayerUi = CreateLayer();
	EnableLayer(LayerUi, true);
	LayerBg = CreateLayer();
	EnableLayer(LayerBg, true);
	

	return true;
}

bool Renderer::OnUserUpdate(float fElapsedTime)
{
	// If resources.pak failed loading, show error message
	if (!bResourcePackLoaded)
	{
		Clear(olc::Pixel(5, 5, 10));
		olc::Pixel pTextC = olc::Pixel(200, 20, 15);
		DrawStringDecal({ 10, 12 }, "FATAL ERROR: Loading file 'resources.pak' failed.", pTextC, { 2.0f, 2.2f });
		DrawStringDecal({ 10, 36 }, "The file might be corrupted, or it doesn't exist.", pTextC, { 2.0f, 2.2f });
		return true;
	}

	// Clears the screen, so we don't have any pixels overlapping
	Clear(olc::BLANK);

	SetDrawTarget(LayerBg);
	// === Background and darken
	DrawDecal({ 0, 0 }, decBackground);
	FillRectDecal({ 0, 0 }, { float(ScreenWidth()), float(ScreenHeight()) }, olc::Pixel(0, 0, 0, 100));
	SetDrawTarget(LayerUi);


	
	// ===
	// === Taskbar
	FillRectDecal({ float(nTaskbarX), float(nTaskbarY) }, { float(nTaskbarW), float(nTaskbarH) }, olc::Pixel(20, 20, 30, 150));
	DrawLine({ nTaskbarX, nTaskbarY }, { nTaskbarW, nTaskbarY }, olc::WHITE);
	// ===

	float fMouseX = GetMouseX();
	float fMouseY = GetMouseY();

	

	
	// Get current system time
	boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();

	// Get specific time from the time object
	int nYear = timeLocal.date().year();
	int nMonth = timeLocal.date().month();
	int nDay = timeLocal.date().day();
	int nHour = timeLocal.time_of_day().hours();
	int nMin = timeLocal.time_of_day().minutes();
	int nSec = timeLocal.time_of_day().seconds();
	// Construct readable time strings
	string sTime = PrependTime(nHour) + ":" + PrependTime(nMin);
	string sTimeLong = PrependTime(nHour) + ":" + PrependTime(nMin) + ":" + PrependTime(nSec);
	string sDate = PrependTime(nDay) + "." + PrependTime(nMonth) + "." + PrependTime(nYear);


	if (bDrawDebugBoundaries)
	{
		DrawRect({ nTaskbarW - 116, nTaskbarY }, { nTaskbarW, nTaskbarH });
	}

	if (GetMouse(0).bPressed)
	{
		if (IsPointInRect({ fMouseX, fMouseY }, { nTaskbarW - 116.0f, nTaskbarY + 0.0f }, { nTaskbarW + 0.0f, nTaskbarH + 0.0f }))
		{
			bTimeBoxOpen = true;
		}
	}

	if (bTimeBoxOpen)
	{
		FillRectDecal({ nTaskbarW - 150.0f, nTaskbarY - 300.0f }, { nTaskbarW + 0.0f, nTaskbarY + 0.0f }, olc::Pixel(10, 10, 20, 100));
		GradientFillRectDecal({ 0.0f, 0.0f }, { 100.2f, 100.5f }, olc::Pixel(255, 0, 0), olc::Pixel(0, 255, 0), olc::Pixel(0, 0, 255), olc::Pixel(255, 255, 0));
	}

	// Inserts logo into taskbar
	DrawDecal({ float(nTaskbarX), float(nTaskbarY) }, decLogo);

	// Draws Time & Date
	DrawStringDecal({ nTaskbarW - 85.0f, nTaskbarH - 36.0f }, sTime, olc::WHITE, { 1.3f, 1.3f });
	DrawStringDecal({ nTaskbarW - 110.0f, nTaskbarH - 24.0f }, sDate, olc::WHITE, { 1.3f, 1.3f });



	return true;
}
