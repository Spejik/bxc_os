#pragma once

#include <iostream>
#include "json.hpp"


using json = nlohmann::json;
using namespace std;

class Utils
{
private:
	string sAppdata = getenv("APPDATA");
	string sConfigPath = sAppdata + "\\bxc_os\\";
	string sConfigFile = "config.json";
	string sConfigLocation = sConfigPath + sConfigFile;
	json jsonConfig;


public:
	int gcd(int a, int b);
	bool LoadConfig();
	bool SaveConfig();

	int    GetConfigIntField   (string key);
	bool   GetConfigBoolField  (string key);
	string GetConfigStringField(string key);

	void SetConfigField(string key, int bFullscreen);
	void SetConfigField(string key, bool bFullscreen);
	void SetConfigField(string key, string bFullscreen);

	bool CreateAppDataDirectory();
	string sFullscreenInfoMessage = "You can change this setting in file " + sConfigLocation;



};

