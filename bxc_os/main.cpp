#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "json.hpp"
using namespace std;

struct window {
	int px;
	int py;
	int sx;
	int sy;
	string name;
};

class bxc_os : public olc::PixelGameEngine
{
public:
	bxc_os()
	{
		sAppName = "BXC OS";
	}

private: 
	string sResourcePackName = "./resources.bxc_pack";
	string sResourcePackKey = "V StarBucks maji novou bagetu: santaislovesantaislife69 XXXl. Objednejte si ji nyni ve vasi mistni pobocce StarBucks";
	olc::Sprite* sprBackground;
	olc::Decal* decBackground;
	olc::ResourcePack* RP = new olc::ResourcePack();
	uint32_t nLayerBackground = 1;
	uint32_t nLayerMain = 2;

public:
	bool OnUserCreate() override
	{
		RP->AddFile("./background.png");
		RP->SavePack(sResourcePackName, sResourcePackKey);

		if (!RP->LoadPack(sResourcePackName, sResourcePackKey))
		{
			DrawString(4, 4, "FATAL ERROR: Loading " + sResourcePackName + " failed.", olc::RED, 2);
			DrawString(4, 28, "The file might be corrupted, or it doesn't exist.", olc::RED, 2);
		}


		sprBackground = new olc::Sprite("./background.png");
		decBackground = new olc::Decal(sprBackground);


		SetDrawTarget(nLayerBackground);
		Clear(olc::BLACK);
		DrawSprite(0, 0, sprBackground, 0.5, 0.5);
		EnableLayer(nLayerBackground, true);
		SetDrawTarget(nLayerMain);
		

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLANK);
		DrawDecal({ 0, 0 }, decBackground, { 0, 0 });
		EnableLayer(nLayerMain, true);

		return true;
	}
};


int main()
{
	bool bUseFullScreen = false;
	bool bUseVsync = false;

	bxc_os os;
	if (os.Construct(1280, 720, 1, 1, bUseFullScreen, bUseVsync))
		os.Start();
	else
		cout << "Constructing BXC OS failed" << endl;

	return 0;
}