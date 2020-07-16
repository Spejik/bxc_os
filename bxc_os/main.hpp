#pragma once

#include <chrono>

#define no_init_all deprecated
#define OLC_PGE_APPLICATION

#define APP_VERSION "0.18"
#define FULLSCREEN_ASK 1
#define FULLSCREEN_ALWAYS 2
#define FULLSCREEN_NEVER 3

#ifndef _USING_JSON
	#define _USING_JSON
	#include <nlohmann/json.hpp>
	using json = nlohmann::json;
#endif


#include "time.h"
#include "fs.h"
#include "Renderer.h"
#include "Utils.h"
#include "http.h"