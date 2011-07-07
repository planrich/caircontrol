/*
    Richard Plangger 2011
*/
#ifndef AIRPORT_H
#define AIRPORT_H

#include <Box2D.h>
#include <SDL/SDL_opengl.h>
#include <list>

#include "texture.h"
#include "plane.h"

class Airport {

public:
    Airport(Texture*,int,int);
    ~Airport();

    void render();
    void update(float tpf);

private:
    std::list<Plane*> * m_pPlanes;
    int m_type;
    b2Vec2 m_center;
    
    Texture* m_pTex;
};



#endif
