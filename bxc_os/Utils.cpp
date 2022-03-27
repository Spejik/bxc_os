#include "Utils.hpp"


bool Config::LoadConfig() 
{
	// Creates bxc_os/config.json in appdata
	CreateAppDataDirectory();
	CreateConfigFile();

	std::string sConfig;
	// Reads the config file
	std::ifstream File(Filesystem::configFileLocation);
	getline(File, sConfig);
	File.close();

	// Parse json
	jsonConfig = json::parse(sConfig);

	return true;
}

// Serializes JSON config and writes it to the config file
bool Config::SaveConfig() 
{
	std::ofstream File(Filesystem::configFileLocation);
	File << jsonConfig.dump();
	File.close();

	return true;
}

int Config::GetConfigIntField(std::string key)
{
	try { return (int) jsonConfig[key]; }
	catch ([[maybe_unused]] const std::exception& e) { return JSON_UNDEFINED_INT; }
}
bool Config::GetConfigBoolField(std::string key)
{
	try { return (bool) jsonConfig[key]; }
	catch ([[maybe_unused]] const std::exception& e) { return false; }
}
std::string Config::GetConfigStringField(std::string key)
{
	try { return (std::string) jsonConfig[key]; }
	catch ([[maybe_unused]] const std::exception& e) { return ""; }
}

void Config::SetConfigIntField(std::string key, int value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void Config::SetConfigBoolField(std::string key, bool value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void Config::SetConfigStringField(std::string key, std::string value)
{
	jsonConfig[key] = value;
	SaveConfig();
}

// Creates bxc_os directory in %appdata%
bool Config::CreateAppDataDirectory()
{
	try 
	{ 
		return std::filesystem::create_directory(Filesystem::configFilePath);
	} 
	catch (const std::exception& e) 
	{
		spdlog::error("Config#CreateAppDataDirectory: {}", e.what());
		return false;
	}
}

// Cretes config.json file in bxc_os appdata
bool Config::CreateConfigFile() 
{
	try 
	{
		bool bConfigFileExists = std::filesystem::exists(Filesystem::configFileLocation);

		if (bConfigFileExists)
			return true;
		else 
		{
			std::ofstream File(Filesystem::configFileLocation);
			File << "{}";
			File.close();
			return true;
		}
	}
	catch (const std::exception& e) 
	{
		spdlog::error("Config#CreateConfigFile: {}", e.what());
		return false;
	}
}