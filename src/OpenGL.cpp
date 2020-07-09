#include "Console.h"
#include "OpenGL.h"
#include "Debug.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"
#include "Lighting.h"

namespace GameEngine
{
	Camera camera(gmath::vec3(0.0f, 0.0f, -5.0f), gmath::posZ);
	Texture* texture;
	float fov = 45.0f;

	OpenGL::OpenGL(const int& WIDTH, const int& HEIGHT, const char* TITLE)
		:_WindowOpenStatus(true), _WIDTH(WIDTH), _HEIGHT(HEIGHT)
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		this->_OpenGLWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
		
		if (this->_OpenGLWindow == nullptr)
		{
			Console::DebugInfo("Failed to create GLFW window", Console::LEVEL::ERROR);
			glfwTerminate();
		}
		Console::DebugInfo("Created window successfully");
		glfwMakeContextCurrent(this->_OpenGLWindow);

		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK)
			Console::DebugInfo("Failed to initialize GLEW", Console::LEVEL::ERROR);
		Console::DebugInfo("Initialized GLEW successfully");

		GLCALL(glViewport(0, 0, WIDTH, HEIGHT));
		GLCALL(glfwSetKeyCallback(_OpenGLWindow, UserInput::key_callback));
		GLCALL(glfwSetCursorPosCallback(_OpenGLWindow, UserInput::mouse_callback));
		GLCALL(glfwSetInputMode(_OpenGLWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
		GLCALL(glfwSetScrollCallback(_OpenGLWindow, UserInput::scroll_callback));
		texture = new Texture("assets/textures/Texture2.jpg");
	}
	OpenGL::~OpenGL()
	{
		delete texture;
		if (_WindowOpenStatus)
			Close();
	}
	void OpenGL::Run()
	{
		_WindowOpenStatus = !glfwWindowShouldClose(_OpenGLWindow);

		BackgroundClear(RGBA(0.0f, 0.0f, 0.0f, 0.0f));		
		
		Movement();
		Render();

		GLCALL(glfwPollEvents());
		GLCALL(glfwSwapBuffers(_OpenGLWindow));
	}

	void OpenGL::BackgroundClear(RGBA color)
	{
		GLCALL(glClearColor(color.x, color.y, color.z, color.w));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void OpenGL::Render() const
	{

		float vertices[] = {
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f
		};

		unsigned int indices[] =
		{
			0,1,2,3,4,5,
			6,7,8,9,10,11,
			12,13,14,15,16,17,
			18,19,20,21,22,23,
			24,25,26,27,28,29,
			30,31,32,33,34,35
		};

		GLCALL(glEnable(GL_BLEND));
		GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		Shader shader("assets/shader/Basic.shader");

		VertexArray vao;
		VertexBuffer vbo(vertices, 36 * 8);
		IndexBuffer ibo(vbo, indices, 6 * 6);

		VertexBufferLayout layout;
		Renderer renderer;

		shader.Bind();
		shader.SetUniform1i("u_Texture", 0);

		float time = glfwGetTime();
		gmath::vec4 color(0.9f, sinf(time)/2.0f + 0.5f, 0.2f, 1.0f);
		shader.SetUniform4f("u_Color", color);
		
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);

		texture->Bind(0);
		vao.AddBuffer(vbo, layout);

		gmath::mat4 proj = gmath::perspective(gmath::DegToRadf(fov), (float)GetWidth()/(float)GetHeight() , 0.1f, 100.0f);

		//gmath::mat4 proj = gmath::ortho(-80.0f, 80.0f, 60.0f, -60.0f, 20.0f, -20.0f) * gmath::scale(10.0f);
		gmath::mat4 mvp = gmath::translate(gmath::vec3(0.0f, 0.0f, 0.0f)) * gmath::rotateY(gmath::DegToRad(time*50.0f));
		mvp = mvp * gmath::rotateZ(gmath::DegToRadf(time*50.0f));

		const float radius = 5.0f;
		//camera.SetCamera(gmath::vec3(0.0f,0.0f,-5.0f),gmath::vec3(radius*sinf(time),0.0f,radius*cosf(time)));
		//gmath::mat4 projection;

		//shader.SetUniformMat4f("u_Model", model);

		GLCALL(glEnable(GL_DEPTH_TEST));
		gmath::vec3 cubePositions[] = {
			gmath::vec3(3.1f, -2.7f, 4.0f),
			gmath::vec3(2.0f, 5.0f, -15.0f),
			gmath::vec3(-1.5f, -2.2f, -2.5f),
			gmath::vec3(-3.8f, -2.0f, -12.3f),
			gmath::vec3(2.4f, -0.4f, -3.5f),
			gmath::vec3(-1.7f, 3.0f, -7.5f),
			gmath::vec3(1.3f, -2.0f, -2.5f),
			gmath::vec3(1.5f, 2.0f, -2.5f),
			gmath::vec3(1.5f, 0.2f, -1.5f),
			gmath::vec3(-1.3f, 1.0f, -1.5f)
		};
		
		shader.Unbind();

		Shader other("assets/shader/Shader.shader");
		gmath::mat4 mat = gmath::rotateY(gmath::DegToRadf(50.0f*time)) * gmath::translate(gmath::vec3(3.0f, 10.0f, 10.0f));

		other.Bind();
		other.SetUniformMat4f("u_Model", mat);
		other.SetUniformMat4f("u_View", camera.GetView());
		other.SetUniformMat4f("u_Projection", proj);

		renderer.Draw(vao, ibo, other);

		other.Unbind();
		vao.Unbind();

		gmath::vec4 position = mat * gmath::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		Lighting light(gmath::vec3(0.7f, 0.6f, 0.1f), 0.2f, gmath::vec3(0.8f, 0.8f, 0.8f), position.ToVec3(), 20.0f);
		VertexArray lightVAO;
		Shader lightShader("assets/shader/Light.shader");

		lightVAO.Bind();
		lightVAO.AddBuffer(vbo, layout);
		lightShader.Bind();

		lightShader.SetUniformMat4f("u_View", camera.GetView());
		lightShader.SetUniformMat4f("u_Projection", proj);
		//lightShader.SetUniform4f("u_ObjectColor");

		lightShader.SetUniform4f("u_CameraPosition", gmath::vec4(camera.GetPosition(), 0.0f));
		lightShader.SetUniform4f("u_LightPosition", gmath::vec4(light.GetLightPosition(), 0.0f));
		lightShader.SetUniform3f("u_AmbientColor", light.GetAmbientLight());
		lightShader.SetUniform3f("u_LightColor", light.GetLightColor());
		lightShader.SetUniform1f("u_SpecularStrength", light.GetSpecStrength());

		for (int i = 0; i < 10; i++)
		{
			gmath::mat4 model = gmath::translate(cubePositions[i]);
			//model = gmath::translate(cubePositions[i]) * gmath::rotateX(gmath::DegToRadf(time*100.0f)) * gmath::rotateZ(gmath::DegToRadf(time*20.0f));
			//model = model * gmath::rotateX(gmath::DegToRadf(-45.0f)) * gmath::rotateY(gmath::DegToRadf(45.0f));
			
			lightShader.SetUniformMat4f("u_Model", model);

			//renderer.Draw(vao, ibo, shader);
			renderer.Draw(lightVAO, ibo, lightShader);
		}

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		/*renderer.Draw(vao, ibo, shader);*/

		//mvp = mat * gmath::rotateZ(gmath::DegToRad(time*50.0f)) * gmath::translate(gmath::vec3(-0.25f, -0.25f, 0.0f))* gmath::scale(0.5f);
		//shader.SetUniformMat4f("u_MVP", mvp);
		//renderer.Draw(vao, ibo, shader);
	}

	void OpenGL::Close() const
	{
		GLCALL(glfwTerminate());
	}

	void OpenGL::Movement() const
	{
		const float speed = 0.05f;
		if (UserInput::keys[GLFW_KEY_W])
			camera.MoveForward(speed);
		if (UserInput::keys[GLFW_KEY_S])
			camera.MoveForward(-speed);
		if (UserInput::keys[GLFW_KEY_A])
			camera.MoveRight(-speed);
		if (UserInput::keys[GLFW_KEY_D])
			camera.MoveRight(speed);
		if (UserInput::keys[GLFW_KEY_SPACE])
			camera.MoveUp(speed);
		if (UserInput::keys[GLFW_KEY_LEFT_SHIFT])
			camera.MoveUp(-speed);
		if (UserInput::keys[GLFW_KEY_Q])
			camera.RotateYaw(-0.03f);
		if (UserInput::keys[GLFW_KEY_E])
			camera.RotateYaw(0.03f);
		if (UserInput::keys[GLFW_KEY_ESCAPE])
			GLCALL(glfwSetWindowShouldClose(this->_OpenGLWindow, GL_TRUE));
		if (UserInput::keys[GLFW_KEY_UP])
			camera.RotatePitch(0.03f);
		if (UserInput::keys[GLFW_KEY_DOWN])
			camera.RotatePitch(-0.03f);
		if (UserInput::keys[GLFW_KEY_LEFT])
			camera.RotateRoll(-0.03f);
		if (UserInput::keys[GLFW_KEY_RIGHT])
			camera.RotateRoll(0.03f);

		camera.RotateYaw(UserInput::mouseMotion.x);
		if (camera.GetPitch() > 89.0f || camera.GetPitch() < -89.0f)
		{
			camera.RotatePitch(89.0f-camera.GetPitch());
			if (camera.GetPitch() > 89.0f)
				camera.SetPitch(89.0f);
			else
				camera.SetPitch(-89.0f);
		}
		else
			camera.RotatePitch(-UserInput::mouseMotion.y);

		if (fov >= 1.0f && fov <= 90.0f)
			fov += UserInput::yOffset*5.0f;
		else if (fov < 1.0f)
			fov = 1.0f;
		else if (fov > 90.0f)
			fov = 90.0f;
		UserInput::yOffset = 0.0f;
		UserInput::mouseMotion = gmath::vec2(0.0f, 0.0f);
	}
}