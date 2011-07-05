#include "texture.h"

#include <iostream>

Texture::Texture(const char * file, bool flags) {
    m_width = 0;
    m_height = 0;
    m_texture = 0;

    int use_flags = SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT;
    if (!flags) {
        flags = SOIL_FLAG_COMPRESS_TO_DXT;
    }
    int channels;
    const unsigned char * data = SOIL_load_image( file, &m_width, &m_height, &channels, 0 );

	m_texture = SOIL_create_OGL_texture ( data,	m_width, m_height, channels, SOIL_CREATE_NEW_ID, 
                use_flags );

    /* check for an error during the load process */
    if( 0 == m_texture )
    {
        std::cout << "SOIL loading error: " <<  SOIL_last_result() << std::endl;
    }
}

Texture::~Texture() {

}

void Texture::bind() {
    glBindTexture( GL_TEXTURE_2D, m_texture );
}


