
#include <Box2D.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <list>

#include "plane.h"
#include "texture.h"
#include "gui.h"

#define PLAY 1
#define PAUSE 2
#define MENU 3

#define WIDTH 1366
#define HEIGHT 768

static int gamestate = MENU;

std::list<Plane*> * planes;

void init_SDL();
void drawBackground();
void startNewGame();
void handleInput();
void clearPlanes();

Texture * aircraft0 = NULL;
Texture * airport0 = NULL;
Texture * airport1 = NULL;
Texture * background = NULL;
SDL_Surface * surface;

Plane * focus = NULL;
Gui * gui = NULL;

unsigned int score = 0;
static bool run = true;

int main(int arg, char **args) {

    init_SDL();

    background = new Texture("img/background/background0.jpg"); 
    aircraft0 = new Texture("img/aircraft/aircraft0.png");
    airport0 = new Texture("img/airport/airport0.png");
    airport1 = new Texture("img/airport/airport1.png");

    planes = new std::list<Plane*>();
    gui = new Gui(WIDTH,HEIGHT);

#ifdef DEBUG
    startNewGame();
#endif

    float tpf = 0.f;
    int now = SDL_GetTicks();

    while ( run ) {
        now = SDL_GetTicks();
        glLoadIdentity();

        drawBackground();

        std::list<Plane*>::iterator  it;
        for (it = planes->begin(); it != planes->end(); it++) {
            Plane * plane = *it;
            if (gamestate == PLAY) { plane->update(tpf); }
            plane->render();
        }
        
        gui->update(tpf);
        gui->render(gamestate);
        
        handleInput();
        
        SDL_GL_SwapBuffers();
        SDL_Delay(30);
        tpf = (SDL_GetTicks() - now) / 1000.f;
    }

    clearPlanes();
    delete planes;    
    delete background;
    delete aircraft0;
    delete airport0;
    delete airport1;
    delete gui;

    SDL_Quit();

    return 0;
}

void handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                run = false;
                break;
            }
            case SDL_KEYDOWN: {
                /*if (event.key.keysym == SDLK_ESCAPE) {
                    run = false;
                }*/
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                int x,y;
                SDL_GetMouseState(&x,&y);
            
                bool consumed = gui->mouseDown(x,y);

                if (gamestate == PLAY && !consumed) {       

                    b2PolygonShape B;
                    b2Transform transB;
                    b2Vec2 c (5,5);
                    B.SetAsBox(10.f,10.f,c,0.f);
                    b2Vec2 p1 (x,y);
                    transB.Set(p1,0);

                    std::list<Plane*>::iterator  it;
                    for (it = planes->begin(); it != planes->end(); it++) {
                        Plane * plane = *it;
                        if (plane->control(&B,&transB)) {
                            focus = plane;
                            focus->clearCheckpoints();
                            break;
                        }
                    }
                }

                break;
            }
            case SDL_MOUSEBUTTONUP: {
                focus = NULL;
                break;
            }
            case SDL_MOUSEMOTION: {
                if (focus && gamestate == PLAY) {
                    b2Vec2 point(event.motion.x,event.motion.y);
                    focus->addCheckpoint(&point);
                }
                break;
            }
        }
    }
}

void init_SDL() {

#ifdef RELEASE
    unsigned int flags = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN;
    SDL_ShowCursor(SDL_DISABLE);
#else
    unsigned int flags = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL;
#endif
    
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    surface = SDL_SetVideoMode(WIDTH, HEIGHT, 32, flags);

    glViewport(0,0,WIDTH,HEIGHT);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.2f);
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}



void drawBackground() {
    background->bind();
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(0, 0);    
        glTexCoord2i(0, 1); glVertex2f(0, 768);
        glTexCoord2i(1, 1); glVertex2f(1366, 768);
        glTexCoord2i(1, 0); glVertex2f(1366, 0); 
    glEnd();
}

void clearPlanes() {
    while (planes->size() > 0) {
        Plane * p = planes->front();
        planes->pop_front();
        delete p;
        p = 0;
    }
}

void startNewGame() {

    gamestate = PLAY;

    score = 0;
    
    clearPlanes();
    
    for (int i = 400; i < 800; i+=55) {
        planes->push_front(new Plane(aircraft0,i,625,0,0));
    }
}
