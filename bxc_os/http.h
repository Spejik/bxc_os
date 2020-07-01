#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <boost/algorithm/string/join.hpp>
#include <curl/curl.h>

using namespace std;

class Http
{
public:
	string GetVersion();
	// Downloads resources.pak and puts them into appdata folder
	bool GetResources();
	// Looks up all files that need to be downloaded and downloads them :pepege:
	bool GetUpdate();

private:
	string Get(string endpoint);
	string sUrl = "http://178.63.148.0:44214/"; 
	string sRemoteVersion = "";
	string sAppdata = getenv("APPDATA");
	string sAppdataDirectory = sAppdata + "\\bxc_os\\";
};

