#include "plane.h"
#include <cmath>

#include <iostream>

Plane::Plane(Texture* tex,int centerx, int centery, float angle, int type) {
    m_pTex = tex;
    m_type = type;
    m_speed = 15;
    m_landing = false;
    m_angle = angle;
    m_center.Set(centerx,centery);
    m_pCheckpoints = new std::list<Checkpoint*>();
}

Plane::~Plane() {
    //MEMLEAK m_pCheckpoints items
    while (m_pCheckpoints->size() > 0) { 
        Checkpoint * p = (Checkpoint*)*m_pCheckpoints->begin();
        m_pCheckpoints->pop_front();   
        delete p;
        p = 0;
    }

    delete m_pCheckpoints;
    m_pCheckpoints = 0;
}

void Plane::update(float tpf) {

    if (m_pCheckpoints->size() > 0) {
        Checkpoint * cp = m_pCheckpoints->front();

        b2Vec2 up(0,1);
        b2Vec2 dir =  m_center - *cp->center();

        float len = dir.Normalize();

        if (len <= 10) {
            m_pCheckpoints->pop_front();
            delete cp;
            cp = 0;
        } else {
            float angle = acos(up.x * dir.x + up.y * dir.y);
            //std::cout << angle << std::endl;
            
        
            if (0 < dir.x) {      
                m_angle = M_PI * 2 - angle;
            } else {
                m_angle = angle;
                //aircraft.rotate(rad * (180 / Math.PI));
            } 
            //m_angle = angle;
        } 
    }

    b2Vec2 direction (sin(m_angle),-cos(m_angle));

    b2Vec2 newcenter (m_center.x + (direction.x * m_speed) * tpf,m_center.y + (direction.y * m_speed) * tpf);

    m_center = newcenter;
}

void Plane::render() {
    float whalf = m_pTex->W() / 2.f;
    float hhalf = m_pTex->H() / 2.f;

    glTranslatef((int)m_center.x,(int)m_center.y,0);
    glRotatef(m_angle * (180.f / M_PI) ,0,0,1);

    m_pTex->bind();
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i((int)-whalf, (int)-hhalf);    
        glTexCoord2i(0, 1); glVertex2i((int)-whalf, (int)hhalf);
        glTexCoord2i(1, 1); glVertex2i((int)whalf, (int)hhalf);
        glTexCoord2i(1, 0); glVertex2i((int)whalf, (int)-hhalf);
    glEnd();

    glLoadIdentity();

    std::list<Checkpoint*>::iterator  it;
    for (it = m_pCheckpoints->begin(); it != m_pCheckpoints->end(); it++) {
        Checkpoint * cp = *it;
        cp->render();
    }
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

bool Plane::control(b2PolygonShape * B,b2Transform * transB) {
    b2Manifold manifold;
    b2PolygonShape A;
    b2Transform transA;

    fill(A,transA);

    b2CollidePolygons(&manifold, &A, transA, B, *transB);
    if (manifold.pointCount > 0) {
        return true;
    }

    return false;
}

void Plane::addCheckpoint(b2Vec2 * at) {
    
    if (m_pCheckpoints->size() == 0) {
        b2Vec2 dir = m_center - *at;
        if (dir.Length() > 50) {
            Checkpoint * p = new Checkpoint(*at);
            m_pCheckpoints->push_back(p);
        }
    } else {
        Checkpoint * last = m_pCheckpoints->back();
        if (last->distance(*at) > 25) {
            Checkpoint * p = new Checkpoint(*at);
            m_pCheckpoints->push_back(p);
        }
    }
}
