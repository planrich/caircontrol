/*
    Richard Plangger 2011
*/
#ifndef GUIITEM_H
#define GUIITEM_H

#include <Box2D.h>
#include <SDL/SDL_opengl.h>

#include "texture.h"

class GuiItem {

public:
    GuiItem(const char *,int,int,int,int);
    ~GuiItem();

    void render(int gamestate);
    void update(float tpf);
    bool mouseDown(int,int);

    bool isClicked(int,int);

    void setPassiv(const char *);
    void state(bool active) { m_active = active; };
    

private:
    bool m_active;
    b2Vec2 m_center;
    b2Vec2 m_dimension;
    
    Texture * m_pActive;
    Texture * m_pPassiv;
};

#endif
