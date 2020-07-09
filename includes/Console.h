#pragma once

#include <string>
#include "Core.h"

namespace GameEngine
{
	class GAME_ENGINE_API Console
	{
	public:
		enum LEVEL : int
		{
			INFO = 0, WARNING = 1, ERROR = 2
		};

		Console();
		~Console();

		static inline void SetDebugInfoLevel(LEVEL level) { debugLevel = level; }
		static void DebugInfo(const char* info, LEVEL level = LEVEL::INFO);
		static void DebugInfo(const std::string& info, LEVEL level = LEVEL::INFO);

		static void Log(const char* out);
		static void Log(const std::string& out);
		
		static void LogLine(const char* out);
		static void LogLine(const std::string& out);

		static char Get(void);
		static std::string GetLine(void);

	private:
		static LEVEL debugLevel;
	};
}