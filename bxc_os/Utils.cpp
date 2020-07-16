#include "Utils.h"


int Utils::gcd(int a, int b) 
{
	return (b == 0) ? a : gcd(b, a%b);
};

bool Utils::LoadConfig() {
	// Creates bxc_os/config.json in appdata
	CreateAppDataDirectory();
	CreateConfigFile();

	std::string sConfig;
	// Reads the config file
	std::ifstream File(sConfigFileLocation);
	getline(File, sConfig);
	File.close();

	// Parse json
	jsonConfig = json::parse(sConfig);

	return true;
}

// Serializes JSON config and writes it to the config file
bool Utils::SaveConfig() {
	std::ofstream File(sConfigFileLocation);
	File << jsonConfig.dump();
	File.close();

	return true;
}


int Utils::GetConfigIntField(std::string key)
{
	try { return (int) jsonConfig[key]; }
	catch (std::exception e) { return JSON_UNDEFINED_INT; }
}
bool Utils::GetConfigBoolField(std::string key)
{
	try { return (bool) jsonConfig[key]; }
	catch (std::exception e) { return false; }
}
std::string Utils::GetConfigStringField(std::string key)
{
	try { return (std::string) jsonConfig[key]; }
	catch (std::exception e) { return ""; }
}



void Utils::SetConfigIntField(std::string key, int value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void Utils::SetConfigBoolField(std::string key, bool value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void Utils::SetConfigStringField(std::string key, std::string value)
{
	jsonConfig[key] = value;
	SaveConfig();
}


// Creates bxc_os directory in %appdata%
bool Utils::CreateAppDataDirectory()
{
	try { 
		return boost::filesystem::create_directory(sConfigFilePath); 
	} 
	catch (std::exception e) {
		std::cout << e.what() <<  std::endl;
		return false;
	}
}

// Cretes config.json file in bxc_os appdata
bool Utils::CreateConfigFile() {
	try {
		struct stat buffer;
		bool bConfigFileExists = (stat(sConfigFileLocation.c_str(), &buffer) == 0);

		if (bConfigFileExists)
			return true;
		else 
		{
			std::ofstream File(sConfigFileLocation);
			File << "{}";
			File.close();
			return true;
		}
		
	}
	catch (std::exception e) {
		std::cout << e.what() <<  std::endl;
		return false;
	}
}