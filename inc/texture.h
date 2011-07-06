/*
    Richard Plangger 2011
*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>

class Texture {

public:
    Texture(const char * file, bool flags);
    ~Texture();

    void bind();

    int W() { return m_width; };
    int H() { return m_height; };

private:
    GLuint m_texture;
    int m_width;
    int m_height;	
};



#endif
