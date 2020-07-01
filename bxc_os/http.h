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
	size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp);
	string _url = "http://178.63.148.0:44214/"; 
	string _auth = "app:gQKX5cWdRsYaWrqq";
	string _REMOTE_VERSION = "";
};

