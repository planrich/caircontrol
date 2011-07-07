#include "airport.h"
#include <cmath>

Airport::Airport(Texture* tex,int centerx, int centery) {
    m_pTex = tex;
    m_center.Set(centerx,centery);
    m_pPlanes = new std::list<Plane*>();
}

Airport::~Airport() {

}

void Airport::update(float tpf) {

}

void Airport::render() {

    float whalf = m_pTex->W() / 2.f;
    float hhalf = m_pTex->H() / 2.f;

    glTranslatef((int)m_center.x,(int)m_center.y,0);

    m_pTex->bind();
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i((int)-whalf, (int)-hhalf);    
        glTexCoord2i(0, 1); glVertex2i((int)-whalf, (int)hhalf);
        glTexCoord2i(1, 1); glVertex2i((int)whalf, (int)hhalf);
        glTexCoord2i(1, 0); glVertex2i((int)whalf, (int)-hhalf);
    glEnd();

    glLoadIdentity();
}

