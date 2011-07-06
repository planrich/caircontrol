#include "texture.h"

#include <iostream>

Texture::Texture(const char * file, bool flags) {
    m_width = 0;
    m_height = 0;
    m_texture = 0;

    SDL_Surface * img = IMG_Load(file);

    m_width = img->w;
    m_height = img->h;

    int nOfColors = img->format->BytesPerPixel;
    int texture_format = GL_RGB;
    if (nOfColors == 4)     // contains an alpha channel
    {
            if (img->format->Rmask == 0x000000ff)
                    texture_format = GL_RGBA;
            else
                    texture_format = GL_BGRA;
    } else if (nOfColors == 3)     // no alpha channel
    {
            if (img->format->Rmask == 0x000000ff)
                    texture_format = GL_RGB;
            else
                    texture_format = GL_BGR;
    } else {
            printf("warning: the image is not truecolor..  this will probably break\n");
            // this error should not go unhandled
    }

	glGenTextures( 1, &m_texture );

	glBindTexture( GL_TEXTURE_2D, m_texture );
 
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, img->w, img->h, 0,
                      texture_format, GL_UNSIGNED_BYTE, img->pixels );

    SDL_FreeSurface( img );

    /*int use_flags = SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT;
    if (!flags) {
        flags = SOIL_FLAG_COMPRESS_TO_DXT;
    }
    int channels;
    const unsigned char * data = SOIL_load_image( file, &m_width, &m_height, &channels, 0 );

	m_texture = SOIL_create_OGL_texture ( data,	m_width, m_height, channels, SOIL_CREATE_NEW_ID, 
                use_flags );

     check for an error during the load process 
    if( 0 == m_texture )
    {
        std::cout << "SOIL loading error: " <<  SOIL_last_result() << std::endl;
    }*/
}

Texture::~Texture() {
    glDeleteTextures( 1, &m_texture );
}

void Texture::bind() {
    glBindTexture( GL_TEXTURE_2D, m_texture );
}


