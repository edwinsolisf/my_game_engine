#include "UserInput.h"

namespace GameEngine
{
	bool UserInput::keys[1024] = { false };
	bool UserInput::firstMouse = true;
	float UserInput::sensitivity = 0.005f;
	float UserInput::yOffset = 0.0f;
	gmath::vec2 UserInput::lastPos = gmath::vec2(400.0f, 300.0f);
	gmath::vec2 UserInput::mouseMotion = gmath::vec2(0.0f, 0.0f);

	void UserInput::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

	void UserInput::mouse_callback(GLFWwindow * window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastPos = gmath::vec2(xpos, ypos);
			firstMouse = false;
		}
		gmath::vec2 offset = gmath::vec2(xpos, ypos) - lastPos;
		lastPos = gmath::vec2(xpos, ypos);
		mouseMotion = offset * sensitivity;
	}

	void UserInput::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
	{
		yOffset = yoffset;
	}

	UserInput::UserInput()
	{
	}

	UserInput::~UserInput()
	{
	}

	void UserInput::RegisterUserInput()
	{
		RegisterMouseInput();
		RegisterKeyInput();
	}
}