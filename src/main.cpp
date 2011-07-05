
#include <Box2D.h>
#include <GL/glfw.h>
#include <GL/gl.h>
#include <list>

#include "plane.h"
#include "texture.h"

#include <iostream>

using namespace std;

list<Plane*> * planes;

void init_GLFW();
void draw_background();

Texture * aircraft0 = NULL;
Texture * background = NULL;

int main(int arg,char **args) {

    init_GLFW();

    background = new Texture("img/background/background0.jpg", true); 
    aircraft0 = new Texture("img/aircraft/aircraft0.png", false); 

    planes = new list<Plane*>();

    bool run = true;

    Plane * o = new Plane(aircraft0,0,0,1.5f,0);
    Plane * t = new Plane(aircraft0,400,200,-1.5f,0);
    
    planes->push_front(o);
    planes->push_front(t);

    while ( run ) {

        glLoadIdentity();

        draw_background();

        list<Plane*>::iterator  it;
        for (it = planes->begin(); it != planes->end(); it++) {
            Plane * plane = *it;
            plane->render();
        }

        if (o->crashes(t)) {
            std::cout << "collision" << std::endl;
        }
        
        int x,y;
        glfwGetMousePos( &x, &y );
        o->setCenter(x,y);


        glfwSwapBuffers();

        run = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
        
        //glfwSleep(30);
    }

    glfwTerminate();

    return 0;
}

void init_GLFW() {

#ifdef RELEASE
    int mode = GLFW_FULLSCREEN;
    int width = 1366;
    int height = 768;
#else
    int mode = GLFW_WINDOW;
    int width = 800;
    int height = 600;
#endif
    
    glfwInit();
    glfwOpenWindow(width,height,0,0,0,0,24,8,mode);

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

    glfwSwapInterval(1);

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
