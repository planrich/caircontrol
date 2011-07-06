#include "plane.h"
#include <cmath>

#include <iostream>

Plane::Plane(Texture* tex,int centerx, int centery, float angle, int type) {
    m_pTex = tex;
    m_type = type;
    m_speed = 50;
    m_landing = false;
    m_angle = angle;
    m_center.Set(centerx,centery);
}

Plane::~Plane() {
    
}

void Plane::update(float tpf) {

    b2Vec2 direction (sin(m_angle),-cos(m_angle));

    b2Vec2 newcenter (m_center.x + (direction.x * m_speed) * tpf,m_center.y + (direction.y * m_speed) * tpf);

    m_center = newcenter;
}

void Plane::render() {
    float whalf = m_pTex->W() / 2.f;
    float hhalf = m_pTex->H() / 2.f;

    glTranslatef(m_center.x,m_center.y,0);
    glRotatef(m_angle * (180.f / M_PI) ,0,0,1);

#ifdef DEBUG
    glColor3f(255,0,0);
    glBegin(GL_QUADS);
        glVertex2f(-whalf, -hhalf);    
        glVertex2f(-whalf, hhalf);
        glVertex2f(whalf, hhalf);
        glVertex2f(whalf, -hhalf);
    glEnd();
    glColor3f(255,255,255);
#else
    m_pTex->bind();
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(-whalf, -hhalf);    
        glTexCoord2i(0, 1); glVertex2f(-whalf, hhalf);
        glTexCoord2i(1, 1); glVertex2f(whalf, hhalf);
        glTexCoord2i(1, 0); glVertex2f(whalf, -hhalf);
    glEnd();
#endif
    glLoadIdentity();
}

void Plane::setCenter(int x,int y) {
    m_center.Set(x,y);
}

void Plane::fill(b2PolygonShape& shape, b2Transform& transform) {

    int width = m_pTex->W();
    int height = m_pTex->H();

    b2Vec2 c (width/2,height/2);
    shape.SetAsBox(width/2,height/2,c,m_angle);
    
    b2Vec2 p1 (m_center.x ,m_center.y);
    //printf("%d/%d\n",other->center_x,other->center_y);
    transform.Set(p1,0);
}

bool Plane::crashes(Plane * other) {

    if (m_landing || other->m_landing) {
        return false;
    }

    b2Manifold manifold;
    b2PolygonShape A,B;
    b2Transform transA, transB;

    fill(A,transA);
    other->fill(B,transB);


    b2CollidePolygons(&manifold, &A, transA, &B, transB);
    if (manifold.pointCount > 0) {
        //printf("collision (%d) %d/%d\n",manifold.pointCount,other->center_x,other->center_y);
        return true;
    }
    return false;
}
