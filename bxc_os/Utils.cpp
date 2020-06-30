#include "Utils.h"
#include <filesystem>
#include <fstream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;


int Utils::gcd(int a, int b) 
{
	return (b == 0) ? a : gcd(b, a%b);
};

bool Utils::LoadConfig() {
	string sConfig;
	// Reads the config file in %appdata%/bxc_os
	ifstream File(sConfigLocation);
	// Assigns the file content to variable sConfig
	getline(File, sConfig);
	// Close the file to prevent memory leaks
	File.close();
	// Parse json
	jsonConfig = json::parse(sConfig);

	return true;
}

// Serializes JSON config and writes it to the config file
bool Utils::SaveConfig() {
	ofstream File(sConfigLocation);
	File << jsonConfig.dump();
	File.close();

	return true;
}


int Utils::GetConfigIntField(string key)
{
	try { return (int) jsonConfig[key]; }
	catch (exception e) { return 0; }
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
		return filesystem::create_directory(sConfigPath); 
	} 
	catch (exception e) {
		cout << e.what() << endl;
		return false;
	}
}
