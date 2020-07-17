#include "Renderer.h"


Renderer::Renderer()
{
	sAppName = "BXC OS";
	SetAppName("initializing");
}


float Renderer::RandFloatRange(float min, float max)
{
	return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void Renderer::PackageResourcePack()
{
	std::string sAssetsPath = "assets/";

	for (auto & entry : boost::filesystem::recursive_directory_iterator(sAssetsPath))
	{
		// Ignore plain directories
		if (boost::filesystem::is_directory(entry))
			continue;

		// Ignore svg files, as they're the source files for most assets... and don't get encrypted
		if (entry.path().extension().string() == ".svg")
			continue;

		RP->AddFile(entry.path().string());
	}
	RP->SavePack(sResourcePackName, sResourcePackKey);
}


bool Renderer::isPointInRect(olc::vf2d point, olc::vf2d start, olc::vf2d end) {
	bool inX = (point.x > start.x && point.x < end.x);
	bool inY = (point.y > start.y && point.y < end.y);
	
	return (inX && inY);
}

void Renderer::SetAppName(std::string name) {
	if (name != "")
		sAppName = "BXC OS - " + name;
	else
		sAppName = "BXC OS";
}


bool Renderer::OnUserCreate()
{
	SetAppName("creating instance");
	//PackageResourcePack();

	// Loads Resource Pack
	if (RP->LoadPack(sResourcePackName, sResourcePackKey))
		bResourcePackLoaded = true;
	else
		return true;

	// Set correct values to taskbar dimensions
	nTaskbarX = 0;
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
	


	SetAppName("");
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

	// =======
	// Logic
	// =======
	float fMouseX = (float)GetMouseX();
	float fMouseY = (float)GetMouseY();

	

	
	// Time
	// Construct readable time strings
	// HH::MM
	std::string sTime =        time->prepend(time->hour()) + ":" + time->prepend(time->minute());
	// HH:MM:SS
	std::string sTimeLong =	   time->prepend(time->hour()) + ":" + time->prepend(time->minute()) + ":" + time->prepend(time->second());
	// DD.MM.YYYY
	std::string sDate =        time->prepend(time->day())  + "." + time->prepend(time->month())  + "." + std::to_string(time->year());
	// DD(st/nd/rd/th) MM YYYY
	std::string sDateVerbal =  sDaysOrdinals[time->day()]  + " " + sMonths[time->month()]        + " " + std::to_string(time->year());
	// monday, tuesday, ...
	std::string sDay =         sDays[time->day_of_week()];

	SetAppName(sDate + " " + sTimeLong);

	// =======
	// Listeners (clicking, buttons, ...)
	// =======

	if (GetMouse(0).bPressed)
	{
		// timebox
		if (isPointInRect({ fMouseX, fMouseY }, { nTaskbarW - 116.0f, nTaskbarY + 0.0f }, { nTaskbarW + 0.0f, nTaskbarH + 0.0f }))
			bTimeBoxOpen = !bTimeBoxOpen;
	}


	// =======
	// Drawing
	// =======

	// Clears the screen
	//Clear(olc::BLANK);

	// Sets layer to background
	SetDrawTarget(LayerBg);

	// Background and darken
	DrawDecal({ 0, 0 }, decBackground);
	FillRectDecal({ 0, 0 }, { float(ScreenWidth()), float(ScreenHeight()) }, olc::Pixel(0, 0, 0, 100));

	// Sets layer to UI
	SetDrawTarget(LayerUi);

	// Taskbar
	FillRectDecal({ float(nTaskbarX), float(nTaskbarY) }, { float(nTaskbarW), float(nTaskbarH) }, olc::Pixel(20, 20, 30, 150));
	DrawLine({ nTaskbarX, nTaskbarY }, { nTaskbarW, nTaskbarY }, olc::WHITE);

	// Inserts logo into taskbar
	DrawDecal({ float(nTaskbarX), float(nTaskbarY) }, decLogo);

	// Draws Time & Date
	DrawStringDecal({ nTaskbarW - 85.0f, nTaskbarH - 36.0f }, sTime, olc::WHITE, { 1.3f, 1.3f });
	DrawStringDecal({ nTaskbarW - 110.0f, nTaskbarH - 24.0f }, sDate, olc::WHITE, { 1.3f, 1.3f });

	// Time box
	if (bTimeBoxOpen)
	{
		float fTopX = nTaskbarW - fTimebarW;
		float fTopY = nTaskbarY - fTimebarH;
		FillRectDecal({ fTopX, fTopY }, { fTimebarW, fTimebarH }, olc::Pixel(10, 10, 20, 200));
		DrawStringDecal({ fTopX + 55.0f, fTopY + 25.0f }, sTimeLong, olc::WHITE, { 3.0f, 3.0f });
		DrawStringDecal({ fTopX + 90.0f, fTopY + 55.0f }, sDay, olc::WHITE, { 1.75f, 1.75f });
		DrawStringDecal({ fTopX + 70.0f, fTopY + 70.0f }, sDateVerbal, olc::WHITE, { 1.5f, 1.5f });

		if (bDrawDebugBoundaries)
			DrawRect({ (int)fTopX + 1, (int)fTopY + 1 }, { (int)fTimebarW - 1, (int)fTimebarH - 1 }, olc::RED);

		if (GetMouse(0).bPressed)
			// If user clicks somewhere else than on the timebox, close it
			if (!isPointInRect({ fMouseX, fMouseY }, { fTopX, fTopY }, { fTimebarW, fTimebarH }))
				bTimeBoxOpen = false;
	}

	// Debug boundaries
	if (bDrawDebugBoundaries)
	{
		DrawRect({ nTaskbarW - 116, nTaskbarY }, { nTaskbarW, nTaskbarH }, olc::GREEN);
	}



	return true;
}
