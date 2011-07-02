
#include <SDL/SDL.h>
#include <Box2D.h>
#include <list>

#include "plane.h"

#include <iostream>

using namespace std;

b2World * world = NULL;
list<Plane*> * planes;

char on_event(SDL_Event * e);
void setup_Physics();

int main(int arg,char **args) {

    setup_Physics();    

    planes = new list<Plane*>();

    SDL_Surface* screen = NULL;

    SDL_Init( SDL_INIT_EVERYTHING );
    screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    
    char run = 1;

    SDL_Event event;

    planes->push_front(new Plane(world,0));

    while ( run ) {
        
        while(SDL_PollEvent(&event)) {
            run = on_event(&event);
        }

        world->Step(1.f/60.f,10,10);
        world->ClearForces();

        list<Plane*>::iterator  it;
        for (it = planes->begin(); it != planes->end(); it++) {
            Plane * plane = *it;
            plane->render(screen);
        }

        SDL_Flip( screen );
        SDL_Delay( 1 );
    }

    SDL_Quit();

    return 0;
}

void setup_Physics() {
    b2Vec2 gravity(0.0f,-1.0f);
    bool doSleep = false;
    world = new b2World(gravity, doSleep);
}


char on_event(SDL_Event * e) {
    if (e->type == SDL_QUIT) {
        return 0;
    }

    return 1;
}
