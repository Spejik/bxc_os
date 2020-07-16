#pragma once

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
using namespace std;

class bxc_fs
{
public:
	string sAppdata = boost::filesystem::temp_directory_path().string();
	string sConfigFilePath = sAppdata + "\\bxc_os\\";
	string sConfigFileName = "config.json";
	string sConfigFileLocation = sConfigFilePath + sConfigFileName;
	string sCurrentDirectory = boost::filesystem::current_path().string() + "/";
};

