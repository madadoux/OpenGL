#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <string>
#include <gl/glew.h>
#include <string>


enum textureType
{
	_2D , cube 
};
	class Texture
	{

	public:

		textureType mTextureType; 
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

		void Config_Texture2D(); 
		void Config_Cube();
	};

#endif
//GLuint loadBMP_custom(const char * imagepath);