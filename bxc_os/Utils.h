#pragma once
#define UNDEFINED_INT -99985

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;



class Utils
{
private:
	string sAppdata = getenv("APPDATA");
	string sConfigFilePath = sAppdata + "\\bxc_os\\";
	string sConfigFileName = "config.json";
	string sConfigFileLocation = sConfigFilePath + sConfigFileName;
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
	bool CreateConfigFile();
};

