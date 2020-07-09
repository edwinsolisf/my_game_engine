#include "Renderer.h"

namespace GameEngine
{
	Renderer::Renderer()
	{
	}
	Renderer::~Renderer()
	{
	}
	void Renderer::Draw(const VertexArray & VAO, const IndexBuffer & IBO, const Shader & shader) const
	{
		VAO.Bind();
		IBO.Bind();
		shader.Bind();
		GLCALL(glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}