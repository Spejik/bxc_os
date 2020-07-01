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

milliseconds Renderer::TimeMS()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

float Renderer::RandFloatRange(float min, float max)
{
	return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void Renderer::PackageResourcePack()
{
	RP->AddFile("./assets/background.png");
	RP->AddFile("./assets/logo_tr_48.png");
	RP->AddFile("./assets/logo_tr_84.png");
	RP->AddFile("./assets/logo_w_48.png");
	RP->AddFile("./assets/logo_w_84.png");
	RP->AddFile("./assets/logo_b_48.png");
	RP->AddFile("./assets/logo_b_84.png");
	RP->SavePack(sResourcePackName, sResourcePackKey);
}

// Calculates if a 2D point is within the boundaries of a rectangle
bool Renderer::IsPointInRect(olc::vf2d point, olc::vf2d start, olc::vf2d end) {
	bool inX = (point.x > start.x && point.x < end.x);
	bool inY = (point.y > start.y && point.y < end.y);
	
	return (inX && inY);
}




// =============
// Public stuff
// =============

bool Renderer::OnUserCreate()
{
	// PackageResourcePack();

	// Loads Resource Pack
	if (RP->LoadPack(sResourcePackName, sResourcePackKey))
		bResourcePackLoaded = true;
	else
		return true;

	// Loads assets
	sprBackground = new olc::Sprite("./assets/background.png", RP);
	sprLogo = new olc::Sprite("./assets/logo_w_48.png", RP);
	// Converts asset sprites to decals
	decBackground = new olc::Decal(sprBackground);
	decLogo = new olc::Decal(sprLogo);

	return true;
}

bool Renderer::OnUserUpdate(float fElapsedTime)
{
	// Clears the screen, so we don't have any pixels overlapping
	Clear(olc::BLANK);

	if (!bResourcePackLoaded)
	{
		Clear(olc::Pixel(5, 5, 10));
		olc::Pixel pTextC = olc::Pixel(200, 20, 15);
		DrawString(10, 12, "FATAL ERROR: Loading file '" + sResourcePackName + "' failed.", pTextC, 2);
		DrawString(10, 36, "The file might be corrupted, or it doesn't exist.", pTextC, 2);
		return true;
	}

	SetPixelMode(olc::Pixel::ALPHA);
	// === Background and darken
	DrawDecal({ 0, 0 }, decBackground);
	FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0, 100));
	// ===
	// === Taskbar
	FillRect({ nTaskbarX, nTaskbarY }, { nTaskbarW, nTaskbarH }, olc::Pixel(20, 20, 30, 150));
	DrawLine({ nTaskbarX, nTaskbarY }, { nTaskbarW, nTaskbarY }, olc::WHITE);
	// ===
	SetPixelMode(olc::Pixel::NORMAL);

	float fMouseX = GetMouseX();
	float fMouseY = GetMouseY();

	// Gets system Time
	time_t Time = time(0);
	tm* TimeNow = localtime(&Time);

	if (GetMouse(0).bPressed)
		cout << (IsPointInRect({ fMouseX, fMouseY }, { 0,0 }, { 200, 200 }) ? "true" : "false") << endl;

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

	// Inserts logo
	DrawDecal({ float(nTaskbarX), float(nTaskbarY) }, decLogo);

	// Draws Time & Date
	DrawString({ nTaskbarW - 92, nTaskbarH - 36 }, sTime, olc::WHITE, 1.5);
	DrawString({ nTaskbarW - 100, nTaskbarH - 24 }, sDate, olc::WHITE, 1.5);

	SetPixelMode(olc::Pixel::NORMAL);


	return true;
}
