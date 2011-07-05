/*
    Richard Plangger 2011
*/
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <GL/glfw.h>
#include <SOIL/SOIL.h>

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
