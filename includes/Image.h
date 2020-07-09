#pragma once

#include <string>
namespace GameEngine
{
	class Image
	{
	private:
		std::string _filePath;
		unsigned char* _buffer;
		unsigned int _width;
		unsigned int _heigth;

	public:
		Image(const std::string& file_path);
		~Image();

		void FreeImage();
		inline unsigned char* LoadImage() { return _buffer; }
		inline const unsigned int& GetHeight() const { return _heigth; }
		inline const unsigned int& GetWidth() const { return _width; }
	};
}
