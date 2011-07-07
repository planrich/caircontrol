/*
    Richard Plangger 2011
*/
#ifndef GUI_H
#define GUI_H

#include <Box2D.h>
#include <SDL/SDL_opengl.h>
#include <list>

#include "guiitem.h"

class Gui {

public:
    Gui(int,int);
    ~Gui();

    void render(int gamestate);
    void update(float tpf);
    bool mouseDown(int,int);

private:
    b2Vec2 m_windowDimensions;
    
    GuiItem * m_pPlay;
    GuiItem * m_pInfo;
    GuiItem * m_pSpeed;
    GuiItem * m_pQuit;
};

#endif
