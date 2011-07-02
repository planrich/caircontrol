#include "plane.h"

Plane::Plane(b2World * world, int type) {
    this->type = type;
    this->speed = 50;
    this->landing = false;

    b2BodyDef def;
    def.position.Set(475,600);
    def.type = b2_dynamicBody;

    this->body = world->CreateBody(&def);
   

    b2PolygonShape box;
    box.SetAsBox(52,52);
    b2FixtureDef fixturedef;
    fixturedef.shape = &box;
    fixturedef.density = 1;
    fixturedef.friction = 0.3f;

    this->body->CreateFixture(&fixturedef);


    this->img = IMG_Load("img/aircraft/aircraft0.png");
    if (!img) {
        printf("IMG_LOAD: %s\n",IMG_GetError());
    }
}

Plane::~Plane() {
    //delete body? actually i think b2 will handle that
    SDL_FreeSurface(this->img);
}

void Plane::render(SDL_Surface * surface) {

    b2Vec2 position = this->body->GetPosition();

    //float32 angle = body->GetAngle();

    SDL_Rect rect = { position.x, position.y, 0, 0 };
    SDL_BlitSurface (this->img, NULL, surface, &rect); 
}
