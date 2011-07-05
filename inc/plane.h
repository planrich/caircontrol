/*
    Richard Plangger 2011
*/
#ifndef PLANE_H
#define PLANE_H

#include <Box2D.h>
#include <GL/gl.h>
#include "texture.h"

class Plane {

public:
    Plane(Texture*,int,int,float,int);
    ~Plane();

    void render();
    void setCenter(int,int);
    bool crashes(Plane * other);
    void fill(b2PolygonShape&, b2Transform&);

private:
    int m_type;
    bool m_landing;
    float m_speed;
    b2Vec2 m_center;
    float m_angle;
    
    Texture* m_pTex;
};



#endif
