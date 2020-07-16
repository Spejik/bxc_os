#pragma once

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>


#ifndef _BXC_FS
#define _BXC_FS


namespace bxc {
	class fs
	{
	public:
		fs();

	public:
		std::string sAppdata = boost::filesystem::temp_directory_path().string();
		std::string sConfigFilePath = sAppdata + "\\bxc_os\\";
		std::string sConfigFileName = "config.json";
		std::string sConfigFileLocation = sConfigFilePath + sConfigFileName;
		std::string sCurrentDirectory = boost::filesystem::current_path().string() + "/";
	};
}
#endif // _BXC_FS