#include "guiitem.h"


GuiItem::GuiItem(const char * tex, int cx, int cy,int width,int height) {
    m_center.Set(cx,cy);
    m_dimension.Set(width,height);
    m_active = true;
    m_pActive = new Texture(tex);
    m_pPassiv = NULL;
}

GuiItem::~GuiItem() {
    delete m_pActive;
    if (m_pPassiv) { delete m_pPassiv; }
}

void GuiItem::setPassiv(const char * tex) {
    m_pPassiv = new Texture(tex);
}

bool GuiItem::mouseDown(int x, int y) {
    return false;
}

void GuiItem::update(float tpf) {

}

bool GuiItem::isClicked(int x,int y) {
    int sx = m_center.x - m_dimension.x / 2;
    int sy = m_center.y - m_dimension.y / 2;

    return (x >= sx && y >= sy && (sx + m_dimension.x) > x && (sy + m_dimension.y) > y);
}

void GuiItem::render(int gamestate) {

    float whalf = m_pActive->W() / 2.f;
    float hhalf = m_pActive->H() / 2.f;

    glTranslatef((int)m_center.x,(int)m_center.y,0);

    if (m_active || m_pPassiv == NULL) {
        m_pActive->bind();
    } else {
        m_pPassiv->bind();
    }

    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i((int)-whalf, (int)-hhalf);    
        glTexCoord2i(0, 1); glVertex2i((int)-whalf, (int)hhalf);
        glTexCoord2i(1, 1); glVertex2i((int)whalf, (int)hhalf);
        glTexCoord2i(1, 0); glVertex2i((int)whalf, (int)-hhalf);
    glEnd();

    glLoadIdentity();


}
