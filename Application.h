#pragma once

#include "Core.h"
#include "OpenGL.h"

#include <iostream>
namespace GameEngine
{
	class GAME_ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Setup();
		virtual void Process();
		virtual void Render();
		virtual void Close();

		inline bool IsRunning() const { return _isRunning; }
	private:
		OpenGL* _window;
		bool _isRunning;
	};

}