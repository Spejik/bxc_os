#include "Utils.h"

bxc::Utils::Utils() {
	LoadConfig();
}

int bxc::Utils::gcd(int a, int b)
{
	return (b == 0) ? a : gcd(b, a%b);
};

bool bxc::Utils::LoadConfig() {
	// Creates bxc_os/config.json in appdata
	CreateAppDataDirectory();
	CreateConfigFile();

	std::string sConfig;
	// Reads the config file
	std::ifstream File(fs->sConfigFileLocation);
	getline(File, sConfig);
	File.close();

	// Parse json
	jsonConfig = json::parse(sConfig);

	return true;
}

// Serializes JSON config and writes it to the config file
bool bxc::Utils::SaveConfig() {
	std::ofstream File(fs->sConfigFileLocation);
	File << jsonConfig.dump();
	File.close();

	return true;
}


int bxc::Utils::GetConfigIntField(std::string key)
{
	try { return (int) jsonConfig[key]; }
	catch (std::exception e) { return JSON_UNDEFINED_INT; }
}
bool bxc::Utils::GetConfigBoolField(std::string key)
{
	try { return (bool) jsonConfig[key]; }
	catch (std::exception e) { return false; }
}
std::string bxc::Utils::GetConfigStringField(std::string key)
{
	try { return (std::string) jsonConfig[key]; }
	catch (std::exception e) { return ""; }
}



void bxc::Utils::SetConfigIntField(std::string key, int value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void bxc::Utils::SetConfigBoolField(std::string key, bool value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void bxc::Utils::SetConfigStringField(std::string key, std::string value)
{
	jsonConfig[key] = value;
	SaveConfig();
}


// Creates bxc_os directory in %appdata%
bool bxc::Utils::CreateAppDataDirectory()
{
	try { 
		return boost::filesystem::create_directory(fs->sConfigFilePath);
	} 
	catch (std::exception e) {
		std::cout << e.what() <<  std::endl;
		return false;
	}
}

// Cretes config.json file in bxc_os appdata
bool bxc::Utils::CreateConfigFile() {
	try {
		struct stat buffer;
		bool bConfigFileExists = (stat(fs->sConfigFileLocation.c_str(), &buffer) == 0);

		if (bConfigFileExists)
			return true;
		else 
		{
			std::ofstream File(fs->sConfigFileLocation);
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