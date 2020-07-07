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
#include <boost/filesystem.hpp>
#include <curl/curl.h>

using namespace std;
using namespace std::chrono;

class Http
{
public:
	string GetVersion();
	// Look up all files that need to be downloaded and downloads them :pepege:
	float GetUpdate();

private:
	string Get(string endpoint);
	string sUrl = "http://178.63.148.0:44214/"; 
	string sRemoteVersion = "";
	string sDirectory = boost::filesystem::current_path().string() + "/";
	int nTimeMs()
	{
		return duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
	}
};

