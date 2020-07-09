#include "Image.h"

#include <fstream>
#include "Console.h"
namespace GameEngine
{
	Image::Image(const std::string & file_path)
		:_filePath(file_path)
	{
		std::ifstream file(file_path, std::ifstream::binary);
		
		unsigned int size;
		char header[3];

		file.get(header, 3);
		
		if (!strcmp(header, "BM"))
		{
			char temp[5] = { 0 };

			file.get(temp,5);
			size = *(unsigned int*)(&temp[0]) - 54;
			
			_buffer = new unsigned char[size] {0};

			for (int i = 0; i < 3; i++)
				file.get(temp, 5); //Dumps next 3 bytes of data

			file.get(temp, 5);
			_width = *(unsigned int*)(&temp[0]);

			file.get(temp, 5);
			_heigth = *(unsigned int*)(&temp[0]);

			for (int i = 0; i < 7; i++)
				file.get(temp, 5); //Dumps next 7 bytes of data

			for (unsigned int i = 0; i < _width*_heigth*3; i+=3)
			{
				unsigned char r = 0, g = 0, b = 0;
				temp[2] = 0;
				temp[3] = 0;

				file.get(temp, 2);
				b = (unsigned char)(temp[0]);
				
				file.get(temp, 2);
				g = (unsigned char)(temp[0]);
				
				file.get(temp, 2);
				r = (unsigned char)(temp[0]);

				_buffer[i] = r;
				_buffer[i+1] = g;
				_buffer[i+2] = b;
			}
			
		}
		else if (!strcmp(header, "P3"))
		{
			unsigned char temp;
			file >> _width;
			file >> _heigth;
			file >> temp;

			_buffer = new unsigned char[_width*_heigth*3] {0};
			for(int i = 0; i < _width*_heigth*3; i+=3)
			{
				file >> temp;
				_buffer[i] = temp;
				file >> temp;
				_buffer[i+1] = temp;
				file >> temp;
				_buffer[i+2] = temp;
			}


		}
		else
		{
			Console::DebugInfo(std::string("Could not open image file: ") + file_path, Console::LEVEL::ERROR);
		}
	}
	Image::~Image()
	{
	}
	void Image::FreeImage()
	{
		delete[] _buffer;
	}
}