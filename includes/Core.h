#pragma once

#ifdef GAME_ENGINE_WINDOWS
	#ifdef GAME_ENGINE_BUILD_DLL
		#define GAME_ENGINE_API __declspec(dllexport)
	#else
		#define GAME_ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Game Engine supported only on Windows
#endif