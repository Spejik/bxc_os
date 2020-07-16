#pragma once

#define JSON_UNDEFINED_INT -99985

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <boost/filesystem.hpp>

#ifndef _BXC_UTILS
#define _BXC_UTILS

#ifndef _USING_JSON
	#define _USING_JSON
	#include <nlohmann/json.hpp>
	using json = nlohmann::json;
#endif

class Utils
{
private:
	std::string sAppdata = getenv("APPDATA");
	std::string sConfigFilePath = sAppdata + "\\bxc_os\\";
	std::string sConfigFileName = "config.json";
	std::string sConfigFileLocation = sConfigFilePath + sConfigFileName;
	json jsonConfig;


public:
	int gcd(int a, int b);
	bool LoadConfig();
	bool SaveConfig();

	
	int    GetConfigIntField        (std::string key);
	bool   GetConfigBoolField       (std::string key);
	std::string GetConfigStringField(std::string key);

	
	void SetConfigIntField     (std::string key, int value);
	void SetConfigBoolField    (std::string key, bool value);
	void SetConfigStringField  (std::string key, std::string value);

	bool CreateAppDataDirectory();
	bool CreateConfigFile();
};

#endif // _BXC_UTILS