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
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
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

	int nLoopStart = nTimeUs();
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
	int nLoopEnd = nTimeUs(); // Is also "saving start", since it's before the saving function :weSmart:
	RP->SavePack(sResourcePackName, sResourcePackKey);
	int nSavingEnd = nTimeUs();

	string sAddingFilesTook = to_string((nLoopEnd - nLoopStart) / 1000);
	string sSavingFileTook = to_string((nSavingEnd - nLoopEnd) / 1000);

	cout << "PackageResourcePack - debug: " << endl
		 << "- Adding files took " << sAddingFilesTook << "ms" << endl
		 << "- Saving file took "  << sSavingFileTook  << "ms" << endl;
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

	// Loads assets
	sprBackground = new olc::Sprite("assets/background.png", RP);
	sprLogo = new olc::Sprite("assets/logo_white.png", RP);
	// Converts asset sprites to decals
	decBackground = new olc::Decal(sprBackground);
	decLogo = new olc::Decal(sprLogo);

	LayerUi = CreateLayer();
	EnableLayer(LayerUi, true);
	LayerBg = CreateLayer();
	EnableLayer(LayerBg, true);
	

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
		DrawStringDecal({ 10, 12 }, "FATAL ERROR: Loading file 'resources.pak' failed.", pTextC, { 2.0f, 2.0f });
		DrawStringDecal({ 10, 36 }, "The file might be corrupted, or it doesn't exist.", pTextC, { 2.0f, 2.0f });
		return true;
	}

	SetDrawTarget(LayerBg);
	// === Background and darken
	DrawDecal({ 0, 0 }, decBackground);
	FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::Pixel(0, 0, 0, 100));
	SetDrawTarget(LayerUi);


	SetPixelMode(olc::Pixel::ALPHA);
	
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
	DrawStringDecal({ nTaskbarW - 92.0f, nTaskbarH - 36.0f }, sTime, olc::WHITE, { 1.5f, 1.5f });
	DrawStringDecal({ nTaskbarW - 100.0f, nTaskbarH - 24.0f }, sDate, olc::WHITE, { 1.5f, 1.5f });

	SetPixelMode(olc::Pixel::NORMAL);


	return true;
}
