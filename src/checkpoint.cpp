#include "checkpoint.h"
#include <cmath>

Checkpoint::Checkpoint(b2Vec2 center) {
    m_center = center;
}

Checkpoint::~Checkpoint() {
    
}
void Checkpoint::render() {
    float whalf = 5 / 2.f;
    float hhalf = 5 / 2.f;

    glTranslatef((int)m_center.x,(int)m_center.y,0);

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glVertex2i((int)-whalf, (int)-hhalf);    
        glVertex2i((int)-whalf, (int)hhalf);
        glVertex2i((int)whalf, (int)hhalf);
        glVertex2i((int)whalf, (int)-hhalf);
    glEnd();
    glEnable(GL_TEXTURE_2D);

    glLoadIdentity();
}

float Checkpoint::distance(b2Vec2 to) {

    b2Vec2 dir = to - m_center;

    return dir.Length();
}
