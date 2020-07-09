#pragma once

#include "VertexBuffer.h"
namespace GameEngine
{
	class IndexBuffer
	{
	private:
		unsigned int _rendererID;
		unsigned int _count;
	public:
		IndexBuffer(const VertexBuffer& vbo, const void* data, const unsigned int& count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline const unsigned int& GetCount() const { return _count; }
	};
}