#pragma once

#include <vector>
#include "Debug.h"

namespace GameEngine
{
	struct VertexBufferElements
	{
		unsigned int count;
		unsigned int type;
		unsigned char normalized;

		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_INT:
				return sizeof(GLint);
			case GL_UNSIGNED_INT:
				return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:
				return sizeof(GLubyte);
			default:
				return 0;
			}
		}
	};
	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElements> _elements;
		unsigned int _stride;

	public:
		VertexBufferLayout()
			:_stride(0)
		{

		}

		~VertexBufferLayout()
		{

		}

		template<typename T>
		void Push(const unsigned int& count)
		{
			static_assert(false);
		}

		template<>
		void Push<float>(const unsigned int& count)
		{
			_elements.push_back({count, GL_FLOAT, GL_FALSE});
			_stride += count * VertexBufferElements::GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<int>(const unsigned int& count)
		{
			_elements.push_back({ count, GL_INT, GL_TRUE });
			_stride += count * VertexBufferElements::GetSizeOfType(GL_INT);
		}

		template<>
		void Push<unsigned int>(const unsigned int& count)
		{
			_elements.push_back({ count, GL_UNSIGNED_INT, GL_TRUE });
			_stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(const unsigned int& count)
		{
			_elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
			_stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElements>& GetElements() const { return _elements; }
		inline const unsigned int& GetStride() const { return _stride; }
	};
}