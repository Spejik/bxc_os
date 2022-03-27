#include "Renderer.hpp"


bRenderer::bRenderer()
{
	sAppName = "BXC OS";
	SetAppName("initializing");
}


float bRenderer::RandFloatRange(float min, float max)
{
	std::default_random_engine eng(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(eng);
}

void bRenderer::PackageResourcePack()
{
	std::string sAssetsPath = "assets/";

	for (auto & entry : std::filesystem::recursive_directory_iterator(sAssetsPath))
	{
		// Ignore plain directories
		if (std::filesystem::is_directory(entry))
			continue;

		// Ignore svg files, as they're the source files for most assets
		if (entry.path().extension().string() == ".svg")
			continue;

		RP->AddFile(entry.path().string());
	}
	RP->SavePack(resourcePackName, resourcePackKey);
}


bool bRenderer::isPointInRect(olc::vf2d point, olc::vf2d start, olc::vf2d end) {
	bool inX = (point.x > start.x && point.x < end.x);
	bool inY = (point.y > start.y && point.y < end.y);
	
	return (inX && inY);
}

void bRenderer::SetAppName(std::string name) {
	if (name != "")
		sAppName = "BXC OS - " + name;
	else
		sAppName = "BXC OS";
}

void bRenderer::SetHighlight(olc::vf2d start, olc::vf2d end) {
	highlight[0] = start;
	highlight[1] = end;
}

void bRenderer::UnsetHighlight() {
	highlight[0] = { 0, 0 };
	highlight[1] = { 0, 0 };
}

void bRenderer::SetHighlightType(eHighlightType type)
{
	HighlightType = type;
}


bool bRenderer::OnUserCreate()
{
	SetAppName("loading...");
	//PackageResourcePack();

	// Loads Resource Pack
	if (RP->LoadPack(resourcePackName, resourcePackKey))
		resourcePackLoaded = true;
	else
		return true;

	// Set correct values for variables
	SetVariables();

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

bool bRenderer::OnUserUpdate(float fElapsedTime)
{
	// If resources.pak failed loading, show error message
	if (!resourcePackLoaded)
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
	std::string sTime = fmt::format("{:02}:{:02}", Time::hour(), Time::minute());
	// HH:MM:SS
	std::string sTimeLong = fmt::format("{:02}:{:02}:{:02}", Time::hour(), Time::minute(), Time::second());
	// DD.MM.YYYY
	std::string sDate = fmt::format("{:02}.{:02}.{:02}", Time::day(), Time::month(), Time::year());
	// DD(st/nd/rd/th) MM YYYY
	std::string sDateVerbal = fmt::format("{} {} {}", daysOrdinals[Time::day()], months[Time::month()], Time::year());
	// monday, tuesday, ...
	std::string sDay = days[Time::day_of_week()];

	SetAppName(fmt::format("{} {}", sDate, sTimeLong));

	// =======
	// Listeners (clicking, buttons, ...)
	// =======

	//if (GetMouse(0).bPressed && bTimeBoxOpen)
	//	// If user clicks somewhere else than on the timebox, close it
	//	if (!isPointInRect({ fMouseX, fMouseY }, { fTimebarX, fTimebarY }, { fTimebarW, fTimebarH }))
	//		bTimeBoxOpen = false;

	// Hover
	if (isPointInRect({ fMouseX, fMouseY }, { taskbarW - 116.0f, taskbarY + 0.0f }, { taskbarW + 0.0f, taskbarH + 0.0f }))
	{
		SetHighlight({ taskbarW - 116.0f, taskbarY + 0.0f }, { taskbarW + 0.0f, taskbarH + 0.0f });
		SetHighlightType(HOVER);
	}
	else
	{
		UnsetHighlight();
		SetHighlightType(NONE);
	}

	// Left mouse
	if (GetMouse(0).bHeld)
	{
		// timebox
		if (isPointInRect({ fMouseX, fMouseY }, { taskbarW - 116.0f, taskbarY + 0.0f }, { taskbarW + 0.0f, taskbarH + 0.0f }))
		{
			// Set the open state only once
			if (GetMouse(0).bPressed)
				timeBoxOpen = !timeBoxOpen;
			SetHighlightType(CLICK);
		}
	}


	// =======
	// Drawing
	// =======

	// Clears the screen
	Clear(olc::BLANK);

	// Sets layer to background
	SetDrawTarget(LayerBg);

	// Background and darken
	DrawDecal({ 0, 0 }, decBackground);
	FillRectDecal({ 0, 0 }, { float(ScreenWidth()), float(ScreenHeight()) }, olc::Pixel(0, 0, 0, 100));

	// Sets layer to UI
	SetDrawTarget(LayerUi);

	// Taskbar
	FillRectDecal({ float(taskbarX), float(taskbarY) }, { float(taskbarW), float(taskbarH) }, olc::Pixel(20, 20, 30, 150));
	DrawLine({ taskbarX, taskbarY }, { taskbarW, taskbarY }, olc::WHITE);

	// Inserts logo into taskbar
	DrawDecal({ float(taskbarX), float(taskbarY) }, decLogo);

	// Draws Time & Date
	DrawStringDecal({ taskbarW - 85.0f, taskbarH - 36.0f }, sTime, olc::WHITE, { 1.3f, 1.3f });
	DrawStringDecal({ taskbarW - 110.0f, taskbarH - 24.0f }, sDate, olc::WHITE, { 1.3f, 1.3f });

	// Time box
	if (timeBoxOpen)
	{
		FillRectDecal({ timeboxX, timeboxY }, { timeboxW, timeboxH }, olc::Pixel(10, 10, 20, 200));
		
		DrawStringDecal({ timeboxX + 20.0f, timeboxY + 20.0f }, sTimeLong, olc::WHITE, { 3.0f, 3.0f });   // 06:54:20
		DrawStringDecal({ timeboxX + 20.0f, timeboxY + 50.0f }, sDay, olc::WHITE, { 1.75f, 1.75f });	    // Sunday
		DrawStringDecal({ timeboxX + 20.0f, timeboxY + 70.0f }, sDateVerbal, olc::WHITE, { 1.5f, 1.5f }); // 1st April 2036
	}

	// Debug boundaries
	if (drawDebugBoundaries)
	{
		DrawRect({ taskbarW - 116, taskbarY }, { taskbarW, taskbarH }, olc::GREEN);

		if (timeBoxOpen)
			DrawRect({ (int)timeboxX + 1, (int)timeboxY + 1 }, { (int)timeboxW - 1, (int)timeboxH - 1 }, olc::RED);
	}

	// Draw current highlight
	switch (HighlightType) 
	{
		case HOVER:
			FillRectDecal(highlight[0], highlight[1], olc::Pixel(230, 230, 230, 20));
			break;

		case CLICK:
			FillRectDecal(highlight[0], highlight[1], olc::Pixel(230, 230, 230, 35));
			break;

		case NONE:
		default:
			break;
	}


	return true;
}
