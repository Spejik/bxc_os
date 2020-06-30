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

	
	void SetConfigIntField     (string key, int value);
	void SetConfigBoolField    (string key, bool value);
	void SetConfigStringField  (string key, string value);

	bool CreateAppDataDirectory();
};

