#pragma once

#include <chrono>

#define no_init_all deprecated
#define OLC_PGE_APPLICATION

#define APP_VERSION "0.3.0"
enum class FULLSCREEN
{
	ASK, ALWAYS, NEVER
};

#ifndef _USING_JSON
	#define _USING_JSON
	#include <nlohmann/json.hpp>
	using json = nlohmann::json;
#endif


#include "Time.hpp"
#include "Filesystem.hpp"
#include "Http.hpp"
#include "Utils.hpp"
#include "Renderer.hpp"
