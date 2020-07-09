#pragma once

namespace GameEngine
{
	class VertexBuffer
	{
	private:
		unsigned int _rendererID;
	public:
		VertexBuffer(const void* buffer, const unsigned int& size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

	};
}