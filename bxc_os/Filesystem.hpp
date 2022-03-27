#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>


namespace Filesystem {

static const std::string tempDir = std::filesystem::temp_directory_path().string();
static const std::string configFilePath = tempDir + "\\bxc_os\\";
static const std::string configFileName = "config.json";
static const std::string configFileLocation = configFilePath + configFileName;
static const std::string currentDirectory = std::filesystem::current_path().string() + "\\";

};
