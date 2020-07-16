#pragma once

#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#ifndef OLC_PGE_APPLICATION
#define OLC_PGE_APPLICATION
#endif
#ifndef APP_VERSION
#define APP_VERSION "0.17"
#endif
#ifndef FULLSCREEN_ASK
#define FULLSCREEN_ASK 1
#endif
#ifndef FULLSCREEN_ALWAYS
#define FULLSCREEN_ALWAYS 2
#endif
#ifndef FULLSCREEN_NEVER
#define FULLSCREEN_NEVER 3
#endif

#include "Renderer.h"
#include "Utils.h"
#include "http.h"