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
#include <boost/filesystem.hpp>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#include "time.h"
#include "fs.h"

#ifndef _BXC_HTTP
#define _BXC_HTTP

#ifndef _USING_JSON
	#define _USING_JSON
	#include <nlohmann/json.hpp>
	using json = nlohmann::json;
#endif

class Http
{
public:
	std::string GetVersion();
	// Look up all files that need to be downloaded and downloads them :pepege:
	float GetUpdate();

private:
	std::string Get(std::string endpoint);
	std::string sUrl = "http://178.63.148.0:44214/";
	std::string sRemoteVersion = "";
	bxc::time* time = new bxc::time();
	bxc::fs* fs = new bxc::fs();
};

#endif // _BXC_HTTP