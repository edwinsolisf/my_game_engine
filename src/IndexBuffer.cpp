#include "IndexBuffer.h"
#include "Debug.h"

namespace GameEngine
{
	IndexBuffer::IndexBuffer(const VertexBuffer& vbo, const void* data, const unsigned int& count)
		:_count(count)
	{
		vbo.Bind();
		GLCALL(glGenBuffers(1, &_rendererID));
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
		static_assert(sizeof(GLuint) == sizeof(unsigned int), "[Compile Error]: Size of 'GLuint' does not not equal size of 'unsigned int'");
		GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCALL(glDeleteBuffers(1, &_rendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}
