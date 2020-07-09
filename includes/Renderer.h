#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
namespace GameEngine
{
	class Renderer
	{
	private:

	public:
		Renderer();
		~Renderer();

		void Draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const;
	};
}