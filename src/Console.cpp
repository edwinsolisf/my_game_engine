#include "Console.h"

#include <iostream>
namespace GameEngine
{

	Console::Console()
	{
	}
	Console::~Console()
	{
	}
	void Console::DebugInfo(const char * info, LEVEL level)
	{
		if ((int)level >= debugLevel)
		{
			switch (level)
			{
			case GameEngine::Console::INFO:
				std::cout << "[INFO]: ";
				break;
			case GameEngine::Console::WARNING:
				std::cout << "[WARNING]: ";
				break;
			case GameEngine::Console::ERROR:
				std::cout << "[ERROR]: ";
				break;
			}
			std::cout << info << std::endl;
		}
	}
	void Console::DebugInfo(const std::string & info, LEVEL level)
	{
		if ((int)level >= debugLevel)
		{
			switch (level)
			{
			case GameEngine::Console::INFO:
				std::cout << "[INFO]: ";
				break;
			case GameEngine::Console::WARNING:
				std::cout << "[WARNING]: ";
				break;
			case GameEngine::Console::ERROR:
				std::cout << "[ERROR]: ";
				break;
			}
			std::cout << info << std::endl;
		}
	}
	void Console::Log(const char * out)
	{
		std::cout << out;
	}
	void Console::Log(const std::string & out)
	{
		std::cout << out;
	}
	void Console::LogLine(const char * out)
	{
		std::cout << out << std::endl;
	}
	void Console::LogLine(const std::string & out)
	{
		std::cout << out << std::endl;
	}
	char Console::Get(void)
	{
		char temp;
		temp = std::cin.get();
		return temp;
	}
	std::string Console::GetLine(void)
	{
		std::string temp;
		std::cin >> temp;
		return temp;
	}

	Console::LEVEL Console::debugLevel = Console::LEVEL::INFO;
}