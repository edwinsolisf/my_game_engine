#include "Texture.h"
#include "Debug.h"

#include "../dependencies/stbimage/stb_image.h"
#include "Image.h"
namespace GameEngine
{
	Texture::Texture(const std::string & file_path)
		:_rendererID(0), _width(0), _height(0), _BPP(0), _buffer(nullptr)
	{
		
		stbi_set_flip_vertically_on_load(1);
		_buffer = stbi_load(file_path.c_str(), &_width, &_height, &_BPP, 4);

		GLCALL(glGenTextures(1, &_rendererID));
		
		GLCALL(glBindTexture(GL_TEXTURE_2D, _rendererID));

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _buffer));

		GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

		if (_buffer)
			stbi_image_free(_buffer);
		Unbind();
	}
	Texture::~Texture()
	{
		GLCALL(glDeleteTextures(1, &_rendererID));
	}
	void Texture::Bind(const unsigned int& slot) const
	{
		GLCALL(glActiveTexture(GL_TEXTURE0+slot));
		GLCALL(glBindTexture(GL_TEXTURE_2D, _rendererID));
	}
	void Texture::Unbind() const
	{
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	}
}