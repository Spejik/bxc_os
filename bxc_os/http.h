#pragma once

#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

class Http
{
public:
	// Downloads version
	string GetVersion();

private:
	string Get(string endpoint);
	string _url = "http://178.63.148.0:44214/"; 
	string _REMOTE_VERSION = "";
};

