#pragma once

constexpr auto JSON_UNDEFINED_INT = (-0xbe-0xc001);

#include "Time.hpp"
#include "Filesystem.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>


#ifndef _USING_JSON
	#define _USING_JSON
	#include <nlohmann/json.hpp>
	using json = nlohmann::json;
#endif

namespace Utils {
	// Greatest common divisor
	inline int gcd(int a, int b)
	{
		return (b == 0) ? a : gcd(b, a % b);
	}
};

namespace Config {
	static json jsonConfig;

	bool LoadConfig();
	bool SaveConfig();

	int    GetConfigIntField(std::string key);
	bool   GetConfigBoolField(std::string key);
	std::string GetConfigStringField(std::string key);

	void SetConfigIntField(std::string key, int value);
	void SetConfigBoolField(std::string key, bool value);
	void SetConfigStringField(std::string key, std::string value);

	bool CreateAppDataDirectory();
	bool CreateConfigFile();
}
