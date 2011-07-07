/*
    Richard Plangger 2011
*/
#ifndef PLANE_H
#define PLANE_H

#include <Box2D.h>
#include <SDL/SDL_opengl.h>
#include <list>

#include "texture.h"
#include "checkpoint.h"

class Plane {

public:
    Plane(Texture*,int,int,float,int);
    ~Plane();

    void render();
    void update(float tpf);
    void setCenter(int,int);
    bool crashes(Plane * other);
    void fill(b2PolygonShape&, b2Transform&);
    bool control(b2PolygonShape*,b2Transform*);
    void addCheckpoint(b2Vec2 * at);
    void clearCheckpoints();

private:
    std::list<Checkpoint*> * m_pCheckpoints;
    int m_type;
    bool m_landing;
    float m_speed;
    b2Vec2 m_center;
    float m_angle;
    
    Texture* m_pTex;
};



#endif
