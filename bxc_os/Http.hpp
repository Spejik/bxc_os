#pragma once

#include "Time.hpp"
#include "Filesystem.hpp"

#include <cpr/cpr.h>
#include <boost/algorithm/string.hpp>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <filesystem>
#include <fstream>


#ifndef _USING_JSON
	#define _USING_JSON
	#include <nlohmann/json.hpp>
	using json = nlohmann::json;
#endif

namespace Http {
	// Remote server version
	std::string GetVersion();
	// Look up all files that need to be downloaded and downloads them :pepege:
	void GetUpdate();

	std::string Get(std::string endpoint);
	std::string ToHex(const std::string& s, bool upper_case);

	static constexpr std::string_view url = "https://cloud.spej.eu/bxc_os/";
}
