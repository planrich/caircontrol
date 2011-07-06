
#include <Box2D.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <list>

#include "plane.h"
#include "texture.h"

#include <iostream>

using namespace std;

#define PLAY 1
#define PAUSE 2
#define MENU 3

int gamestate = PLAY;

list<Plane*> * planes;

void init_SDL();
void draw_background();

Texture * aircraft0 = NULL;
Texture * background = NULL;
SDL_Surface * surface;

Plane * focus = NULL;

int main(int arg,char **args) {

    //init_GLFW();
    init_SDL();

    background = new Texture("img/background/background0.jpg", true); 
    aircraft0 = new Texture("img/aircraft/aircraft0.png", false); 

    planes = new list<Plane*>();

    bool run = true;

    //Plane * o = new Plane(aircraft0,0,0,1.5f,0);
    //Plane * t = new Plane(aircraft0,400,200,-1.5f,0);

    for (int i = 0; i < 800; i+=55) {
        planes->push_front(new Plane(aircraft0,i,625,0,0));
    }

    for (int i = 0; i < 800; i+=55) {
        planes->push_front(new Plane(aircraft0,i,700,0,0));
    }
    
    //planes->push_front(o);
    //planes->push_front(t);

    float tpf = 0.f;
    int now = SDL_GetTicks();

    while ( run ) {
        now = SDL_GetTicks();
        glLoadIdentity();

        draw_background();

        list<Plane*>::iterator  it;
        for (it = planes->begin(); it != planes->end(); it++) {
            Plane * plane = *it;
            plane->update(tpf);
            plane->render();
        }

        /*if (o->crashes(t)) {
            std::cout << "collision" << std::endl;
        }*/
        
        //int x,y;
        //glfwGetMousePos( &x, &y );
        //o->setCenter(x,y);


        //glfwSwapBuffers();
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
    
                    b2PolygonShape B;
                    b2Transform transB;
                    b2Vec2 c (5,5);
                    B.SetAsBox(10.f,10.f,c,0.f);
                    b2Vec2 p1 (x,y);
                    transB.Set(p1,0);

                    list<Plane*>::iterator  it;
                    for (it = planes->begin(); it != planes->end(); it++) {
                        Plane * plane = *it;
                        if (plane->control(&B,&transB)) {
                            focus = plane;
                            break;
                        }
                    }
                    break;
                }
                case SDL_MOUSEBUTTONUP: {
                    focus = NULL;
                    break;
                }
                case SDL_MOUSEMOTION: {
                    if (focus) {
                        b2Vec2 point(event.motion.x,event.motion.y);
                        focus->addCheckpoint(&point);
                    }
                    break;
                }
            }
        }

        //run = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
        
        //glfwSleep(30);
        
        SDL_GL_SwapBuffers();
        SDL_Delay(30);
        tpf = (SDL_GetTicks() - now) / 1000.f;
    }

    SDL_Quit();

    return 0;
}

void init_SDL() {

    int width = 1366;
    int height = 768;
#ifdef RELEASE
    unsigned int flags = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN;
    SDL_ShowCursor(SDL_DISABLE);
#else
    unsigned int flags = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL;
#endif
    
    SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    surface = SDL_SetVideoMode(width, height, 32, flags);

    /*glfwInit();
    glfwOpenWindow(width,height,0,0,0,0,24,8,mode);*/

    glViewport(0,0,width,height);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho (0, width, height, 0, -1, 1);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL, 0.1f);
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    //glfwSwapInterval(1);
}



void draw_background() {
    background->bind();
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(0, 0);    
        glTexCoord2i(0, 1); glVertex2f(0, 768);
        glTexCoord2i(1, 1); glVertex2f(1366, 768);
        glTexCoord2i(1, 0); glVertex2f(1366, 0); 
    glEnd();
}
