#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace GameEngine
{
	class VertexArray
	{
	private:
		unsigned int _rendererID;
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& vblayout);
	};
}