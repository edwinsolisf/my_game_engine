#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GL/glfw3.h>

#include "gmath.h"

#include "Core.h"
#include "UserInput.h"
typedef gmath::Vector<4> RGBA;

namespace GameEngine
{

	class GAME_ENGINE_API OpenGL
	{
	public:
		OpenGL(const int& WIDTH, const int& HEIGHT, const char* TITLE);
		~OpenGL();

		void Run();
		void BackgroundClear(RGBA color);
		void Render() const;
		void Close() const;
		void Movement() const;
		inline bool WindowOpen() const { return _WindowOpenStatus; }
		inline const int& GetWidth() const { return _WIDTH; }
		inline const int& GetHeight() const { return _HEIGHT; }

	private:
		GLFWwindow* _OpenGLWindow;
		bool _WindowOpenStatus;
		const int _WIDTH, _HEIGHT;
	};
}
