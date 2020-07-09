#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include "Console.h"

#ifdef PLATFORM_DEBUG
#define GLCALL(x) x; while(GLenum error = glGetError()) { GameEngine::Console::DebugInfo(std::string("[GL_ERROR]: ")+std::to_string(error) + std::string(" From ") + std::string(#x) + std::string(" in ") +std::string(__FILE__) + std::string(" at line ") + std::to_string(__LINE__), GameEngine::Console::LEVEL::ERROR); }
#else
	#define GLCALL(x) x
#endif