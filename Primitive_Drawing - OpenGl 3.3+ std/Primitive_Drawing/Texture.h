#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <string>
#include <gl/glew.h>
#include <string>



	class Texture
	{

	public:
		/*unsigned*/ int width, height;
		int numComponents;
		unsigned char * data;
		int texUnit;
		void Bind();
		Texture(const std::string& fileName, int texUnit);
		Texture(unsigned char* data, int width, int height, int numComponents, int texUnit_);
		virtual ~Texture();
	protected:
	private:
		Texture(const Texture& texture) {}
		void operator=(const Texture& texture) {}
		GLuint m_texture;


	};

#endif
//GLuint loadBMP_custom(const char * imagepath);