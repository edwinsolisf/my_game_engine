#pragma once
#include <string>

namespace GameEngine
{
	class Texture
	{
	private: 
		unsigned int _rendererID;
		int _width, _height, _BPP;
		unsigned char* _buffer;
	public:
		Texture(const std::string& file_path);
		~Texture();

		void Bind(const unsigned int& slot) const;
		void Unbind() const;

	};
}