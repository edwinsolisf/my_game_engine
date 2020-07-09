#include "Application.h"

namespace GameEngine
{
	Application::Application()
	{
	}

	Application::~Application()
	{
		delete this->_window;
	}

	void Application::Setup()
	{
		this->_isRunning = true;
		this->_window = new OpenGL(800, 600, "Application");
	}

	void Application::Process()
	{
	}

	void Application::Render()
	{
		if (_window->WindowOpen())
			this->_window->Run();
		else
			_isRunning = false;
	}

	void Application::Close()
	{
		if(_window->WindowOpen())
			_window->Close();
	}
}