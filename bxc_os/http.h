#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

class Http
{
public:
	string GetVersion();

private:
	string Get(string endpoint);
	string sUrl = "http://178.63.148.0:44214/"; 
	string sUserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.138 Safari/537.36 OPR/68.0.3618.191";
	string sRemoteVersion = "";
};

