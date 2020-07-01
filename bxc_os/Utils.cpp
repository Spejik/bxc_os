#include "Utils.h"


int Utils::gcd(int a, int b) 
{
	return (b == 0) ? a : gcd(b, a%b);
};

bool Utils::LoadConfig() {
	// Creates bxc_os/config.json in appdata
	CreateAppDataDirectory();
	CreateConfigFile();

	string sConfig;
	// Reads the config file
	ifstream File(sConfigFileLocation);
	getline(File, sConfig);
	File.close();

	// Parse json
	jsonConfig = json::parse(sConfig);

	return true;
}

// Serializes JSON config and writes it to the config file
bool Utils::SaveConfig() {
	ofstream File(sConfigFileLocation);
	File << jsonConfig.dump();
	File.close();

	return true;
}


int Utils::GetConfigIntField(string key)
{
	try { return (int) jsonConfig[key]; }
	catch (exception e) { return UNDEFINED_INT; }
}
bool Utils::GetConfigBoolField(string key)
{
	try { return (bool) jsonConfig[key]; }
	catch (exception e) { return false; }
}
string Utils::GetConfigStringField(string key)
{
	try { return (string) jsonConfig[key]; } 
	catch (exception e) { return ""; }
}



void Utils::SetConfigIntField(string key, int value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void Utils::SetConfigBoolField(string key, bool value)
{
	jsonConfig[key] = value;
	SaveConfig();
}
void Utils::SetConfigStringField(string key, string value)
{
	cout << key << ": " << value << endl;
	jsonConfig[key] = value;
	SaveConfig();
}


// Creates bxc_os directory in %appdata%
bool Utils::CreateAppDataDirectory()
{
	try { 
		return filesystem::create_directory(sConfigFilePath); 
	} 
	catch (exception e) {
		cout << e.what() << endl;
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
			ofstream File(sConfigFileLocation);
			File << "{}";
			File.close();
			return true;
		}
		
	}
	catch (exception e) {
		cout << e.what() << endl;
		return false;
	}
}