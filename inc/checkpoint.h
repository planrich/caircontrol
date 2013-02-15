/*
    Richard Plangger 2011
*/
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <Box2D.h>
#include <SDL/SDL_opengl.h>
#include <list>

#include "texture.h"

class Checkpoint {

public:
    Checkpoint(b2Vec2 center);
    ~Checkpoint();

    void render();
    b2Vec2 * center() { return &m_center; };
    float distance(b2Vec2);


private:
    b2Vec2 m_center;
};



#endif
