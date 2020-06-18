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
	string sResourcePackName = "resources.bxc";
	olc::Sprite* sprBackground;
	olc::Decal* decBackground;
	olc::ResourcePack RP;
	int nLayerBackground;
	int nLayerMain;

public:
	bool OnUserCreate() override
	{
		RP.AddFile("C:\\Users\\spej\\Desktop\\background.png");
		RP.SavePack(sResourcePackName, sResourcePackName);

		RP.LoadPack(sResourcePackName, sResourcePackName);


		sprBackground = new olc::Sprite();
		decBackground = new olc::Decal(sprBackground);

		/* Creates layers */
		nLayerBackground = CreateLayer();
		nLayerMain = CreateLayer();
		olc::ResourcePack();

		SetDrawTarget(nLayerBackground);
		DrawDecal({ 0, 0 }, decBackground, { 0, 0 });
		EnableLayer(nLayerBackground, true);
		SetDrawTarget(nLayerMain);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLANK);
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