#include "VertexArray.h"
#include "Debug.h"

namespace GameEngine
{
	VertexArray::VertexArray()
	{
		GLCALL(glGenVertexArrays(1, &_rendererID));
		GLCALL(glBindVertexArray(_rendererID));
	}
	VertexArray::~VertexArray()
	{
		GLCALL(glDeleteVertexArrays(1, &_rendererID));
	}
	void VertexArray::Bind() const
	{
		GLCALL(glBindVertexArray(_rendererID));

	}
	void VertexArray::Unbind() const
	{
		GLCALL(glBindVertexArray(0));
	}
	void VertexArray::AddBuffer(const VertexBuffer & vbo, const VertexBufferLayout & vblayout)
	{
		Bind();
		vbo.Bind();

		const auto& elements = vblayout.GetElements();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			GLCALL(glEnableVertexAttribArray(i));
			GLCALL(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, vblayout.GetStride(), (void*)offset));

			offset += VertexBufferElements::GetSizeOfType(elements[i].type) * elements[i].count;
		}
	}
}