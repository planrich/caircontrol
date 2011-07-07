#include "gui.h"

#include <iostream>

Gui::Gui(int width,int height) {
    m_windowDimensions.Set(width,height);
    m_pPlay = new GuiItem("img/play.png", 17, 17, 35, 35);
    m_pQuit = new GuiItem("img/quit.png", 1349, 17, 35, 35);
    m_pSpeed = new GuiItem("img/speed.png", 77, 17, 35, 35);
    m_pInfo = new GuiItem("img/info.png", 117, 17, 35, 35);
    
    m_pPlay->setPassiv("img/pause.png");
    m_pSpeed->setPassiv("img/speed2.png");
}

Gui::~Gui() {

    delete m_pPlay;
    delete m_pQuit;
    delete m_pSpeed;
    delete m_pInfo;
}

bool Gui::mouseDown(int x, int y) {

    if (m_pPlay->isClicked(x,y)) {
        //play pause
        std::cout << "play" << std::endl;
        return true;
    } else if (m_pSpeed->isClicked(x,y)) {
        //increase speed
        std::cout << "speed" << std::endl;
        return true;
    } else if (m_pInfo->isClicked(x,y)) {
        //show/hide info
        std::cout << "info" << std::endl;
        return true;
    } else if (m_pQuit->isClicked(x,y)) {
        //quit
        std::cout << "quit" << std::endl;
        return true;
    }


    return false;
}

void Gui::update(float tpf) {

}

void Gui::render(int gamestate) {
    m_pPlay->render(gamestate);
    m_pQuit->render(gamestate);
    m_pSpeed->render(gamestate);
    m_pInfo->render(gamestate);
}
