#pragma once

#include "GL/glew.h"
#include "GL/glfw3.h"
#include "Core.h"
#include "OpenGL.h"

namespace GameEngine
{
	enum KEY : int
	{
		A = GLFW_KEY_A, B = GLFW_KEY_B, C = GLFW_KEY_C, D = GLFW_KEY_D, E = GLFW_KEY_E, F = GLFW_KEY_F, G = GLFW_KEY_G,
		H = GLFW_KEY_H, I = GLFW_KEY_I, J = GLFW_KEY_J, K = GLFW_KEY_K, L = GLFW_KEY_L, M = GLFW_KEY_M, N = GLFW_KEY_N,
		O = GLFW_KEY_O, P = GLFW_KEY_P, Q = GLFW_KEY_Q, R = GLFW_KEY_R, S = GLFW_KEY_S, T = GLFW_KEY_T, U = GLFW_KEY_U,
		V = GLFW_KEY_V, W = GLFW_KEY_W, X = GLFW_KEY_X, Y = GLFW_KEY_Y, Z = GLFW_KEY_Z,

		NUM0 = GLFW_KEY_0, NUM1 = GLFW_KEY_1, NUM2 = GLFW_KEY_2, NUM3 = GLFW_KEY_3, NUM4 = GLFW_KEY_4,
		NUM5 = GLFW_KEY_5, NUM6 = GLFW_KEY_6, NUM7 = GLFW_KEY_7, NUM8 = GLFW_KEY_8, NUM9 = GLFW_KEY_9,

		F1 = GLFW_KEY_F1, F2 = GLFW_KEY_F2, F3 = GLFW_KEY_F3, F4 = GLFW_KEY_F4, F5 = GLFW_KEY_F5, F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7, F8 = GLFW_KEY_F8, F9 = GLFW_KEY_F9, F10 = GLFW_KEY_F10, F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12,

		LSHIFT = GLFW_KEY_LEFT_SHIFT, ESC = GLFW_KEY_ESCAPE, ENTER = GLFW_KEY_ENTER, NONE = GLFW_KEY_UNKNOWN
	};

	static const KEY ALL_KEYS[] = {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		LSHIFT, ESC, ENTER
	};

	class GAME_ENGINE_API UserInput
	{
	protected:
	public:
		
		UserInput();
		virtual ~UserInput();

		virtual void RegisterKeyInput() = 0; //Must be overloaded
		virtual void RegisterMouseInput() = 0; // Must be overloaded

 		virtual void RegisterUserInput(); // Must be on a loop
		
		inline void SetSensitivity(const float& sensitivity) { this->sensitivity = sensitivity; }
		inline const bool& GetKeyPressed(KEY key) const { return keys[(int)key]; }
		inline const gmath::vec2& GetMousePosition() const { return lastPos; }
	private:
		friend class OpenGL;
		static bool keys[1024];
		static bool firstMouse;
		static float sensitivity;
		static gmath::vec2 lastPos;
		static gmath::vec2 mouseMotion;
		static float yOffset;
		static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	};
}
