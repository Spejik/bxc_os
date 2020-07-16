#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "time.h"
#include "fs.h"

using namespace std;

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
	bxc_time* time = new bxc_time();
	bxc_fs* fs = new bxc_fs;
};

