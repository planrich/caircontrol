
#include <Box2D.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <list>

#include "plane.h"
#include "texture.h"

#include <iostream>

using namespace std;

list<Plane*> * planes;

void init_SDL();
void draw_background();

Texture * aircraft0 = NULL;
Texture * background = NULL;
SDL_Surface * surface;

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
        planes->push_front(new Plane(aircraft0,i,625,1,0));
    }

    for (int i = 0; i < 800; i+=55) {
        planes->push_front(new Plane(aircraft0,i,700,-1,0));
    }

    for (int i = 0; i < 800; i+=55) {
        planes->push_front(new Plane(aircraft0,i,800,1,0));
    }

    for (int i = 0; i < 800; i+=55) {
        planes->push_front(new Plane(aircraft0,i,900,-1,0));
    }
    
    //planes->push_front(o);
    //planes->push_front(t);

    float tpf = 0.01f;

    while ( run ) {

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
                }
                case SDL_KEYDOWN: {
                    /*if (event.key.keysym == SDLK_ESCAPE) {
                        run = false;
                    }*/
                }
            }
        }

        //run = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
        
        //glfwSleep(30);
        
        SDL_GL_SwapBuffers();
        SDL_Delay(30);
    }

    SDL_Quit();

    return 0;
}

void init_SDL() {

    int width = 1366;
    int height = 768;
#ifdef RELEASE
    unsigned int flags = SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL | SDL_FULLSCREEN;
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
