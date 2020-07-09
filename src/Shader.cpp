#include "Shader.h"
#include "Debug.h"
#include <fstream>

namespace GameEngine
{
	ShaderProgram Shader::ParseShader(const std::string & file_path)
	{
		ShaderProgram program;

		std::ifstream file(file_path);

		if (file.bad())
			Console::DebugInfo("Could not open shader file", Console::LEVEL::ERROR);

		std::string temp;
		int state = -1;

		while (std::getline(file, temp))
		{
			if (temp == "#shader vertex")
				state = 0; // Set state to vertex shader
			else if (temp == "#shader fragment")
				state = 1; // Set state to fragment shader
			else
				switch (state)
				{
				case 0:
					program.vertexShader += temp + '\n';
					break;
				case 1:
					program.fragmentShader += temp + '\n';
				default:
					break;
				}
		}
		return program;
	}
	unsigned int Shader::CompileShader(unsigned int ShaderType, const std::string & shader)
	{
		unsigned int shaderID = GLCALL(glCreateShader(ShaderType));

		const char* string = shader.c_str();
		GLCALL(glShaderSource(shaderID, 1, &string, nullptr));
		GLCALL(glCompileShader(shaderID));

		int success;
		GLCALL(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success)); // Get compile status of th shader

		if (success == GL_FALSE) //  Get Errors
		{
			int length;
			GLCALL(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCALL(glGetShaderInfoLog(shaderID, length, &length, message));

			Console::DebugInfo(std::string("Shader Compile ") + std::string(message), Console::LEVEL::ERROR);

			GLCALL(glDeleteShader(shaderID));

			return 0;
		}

		return shaderID;
	}
	unsigned int Shader::CreateShader(const std::string & VertexShader, const std::string & FragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

		GLCALL(glAttachShader(program, vs));
		GLCALL(glAttachShader(program, fs));

		GLCALL(glLinkProgram(program));

		int success;
		GLCALL(glGetProgramiv(program, GL_LINK_STATUS, &success)); // Get linking status of the program

		if (success == GL_FALSE) //  Get Errors
		{
			int length;
			GLCALL(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
			char* message = (char*)alloca(length * sizeof(char));
			GLCALL(glGetProgramInfoLog(program, length, &length, message));

			Console::DebugInfo(message, Console::LEVEL::ERROR);

			GLCALL(glDeleteProgram(program));

			return 0;
		}

		GLCALL(glValidateProgram(program));

		GLCALL(glDeleteShader(vs));
		GLCALL(glDeleteShader(fs));

		return program;
	}

	int Shader::GetUniformLocation(const std::string & name)
	{
		if (_uniformLocationCache.find(name) != _uniformLocationCache.end())
			return _uniformLocationCache[name];
		
		int location = GLCALL(glGetUniformLocation(_rendererID, name.c_str()));
		_uniformLocationCache.emplace(name, location);

		if (location == -1)
			Console::DebugInfo(std::string("Uniform '") + name + std::string("' not found"), Console::LEVEL::WARNING);

		return location;
	}
	
	Shader::Shader(const std::string & file_path)
		:_filePath(file_path)
	{
		ShaderProgram program = ParseShader(file_path);
		_rendererID = CreateShader(program.vertexShader, program.fragmentShader);
	}
	Shader::~Shader()
	{
		glDeleteProgram(_rendererID);
	}
	void Shader::Bind() const
	{
		GLCALL(glUseProgram(_rendererID));
	}
	void Shader::Unbind() const
	{
		GLCALL(glUseProgram(0));
	}
	void Shader::SetUniform4f(const std::string & name, const gmath::vec4& value)
	{
		GLCALL(glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w));
	}
	void Shader::SetUniformMat4f(const std::string & name, const gmath::mat4& mat)
	{
		GLCALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, &mat[0][0]));
	}
	void Shader::SetUniform1i(const std::string & name, const int& value)
	{
		GLCALL(glUniform1i(GetUniformLocation(name), value));
	}
	void Shader::SetUniform1f(const std::string & name, const float & value)
	{
		GLCALL(glUniform1f(GetUniformLocation(name), value));
	}
	void Shader::SetUniform3f(const std::string & name, const gmath::vec3 & value)
	{
		GLCALL(glUniform3f(GetUniformLocation(name), value.x, value.y, value.z));
	}
}