#include "plane.h"
#include <GL/gl.h>

Plane::Plane(Texture* tex,int centerx, int centery, float angle, int type) {
    this->m_pTex = tex;
    this->m_type = type;
    this->m_speed = 50;
    this->m_landing = false;
    m_center.Set(centerx,centery);
}

Plane::~Plane() {
    
}

void Plane::render() {
    float whalf = m_pTex->W() / 2.f;
    float hhalf = m_pTex->H() / 2.f;
    glRotatef(m_angle,0,0,0);
    glTranslatef(m_center.x + whalf,m_center.y + hhalf,0);
        m_pTex->bind();
        glBegin(GL_QUADS);
            glTexCoord2i(0, 0); glVertex2f(-whalf, -hhalf);    
            glTexCoord2i(0, 1); glVertex2f(-whalf, hhalf);
            glTexCoord2i(1, 1); glVertex2f(whalf, hhalf);
            glTexCoord2i(1, 0); glVertex2f(whalf, -hhalf); 
        glEnd();
    glLoadIdentity();
}

void Plane::setCenter(int x,int y) {
    
    //this->center_x = x - 52;
    //this->center_y = y;
    //printf("set %d/%d\n",center_x,center_y);
}

void Plane::fill(b2PolygonShape& shape, b2Transform& transform) {

    int width = 52;
    int height = 52;

    b2Vec2 c (width/2,height/2);
    shape.SetAsBox(width/2,height/2,c,m_angle);
    
    b2Vec2 p1 (m_center.x ,m_center.y);
    //printf("%d/%d\n",other->center_x,other->center_y);
    transform.Set(p1,0);
}

bool Plane::crashes(Plane * other) {

    if (this->m_landing || other->m_landing) {
        return false;
    }

    b2Manifold manifold;
    b2PolygonShape A,B;
    b2Transform transA, transB;

    this->fill(A,transA);
    other->fill(B,transB);


    b2CollidePolygons(&manifold, &A, transA, &B, transB);
    if (manifold.pointCount > 0) {
        //printf("collision (%d) %d/%d\n",manifold.pointCount,other->center_x,other->center_y);
        return true;
    }
    return false;
}
