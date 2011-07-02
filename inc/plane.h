/*
    Richard Plangger 2011
*/
#ifndef PLANE_H
#define PLANE_H

#include <Box2D.h>
#include <SDL/SDL_image.h>

class Plane {

public:
    Plane(b2World*,int);
    ~Plane();

    void render(SDL_Surface*);

private:
    int type;
    bool landing;
    float speed;
    b2Body *body;
    SDL_Surface *img;
};



#endif
