#pragma once

#include <string>
#include <unordered_map>
#include "Core.h"
#include "gmath.h"

namespace GameEngine
{
	struct ShaderProgram
	{
		std::string vertexShader;
		std::string fragmentShader;
	};

	class GAME_ENGINE_API Shader
	{
	private:
		std::string _filePath;
		unsigned int _rendererID;
		std::unordered_map<std::string, int> _uniformLocationCache;

		ShaderProgram ParseShader(const std::string& file_path);
		unsigned int CompileShader(unsigned int ShaderType, const std::string& shader);
		unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
		int GetUniformLocation(const std::string& name);

	public:
		Shader(const std::string& file_path);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetUniform1i(const std::string& name, const int& value);
		void SetUniform1f(const std::string& name, const float& value);

		void SetUniform3f(const std::string& name, const gmath::vec3& value);
		void SetUniform4f(const std::string& name, const gmath::vec4& value);

		void SetUniformMat4f(const std::string& name, const gmath::mat4& mat);
	};
}