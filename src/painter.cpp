#include "painter.h"


Painter::Painter()
{
    //m_sprite.setScale(EngineMisc::graphicScale.x,EngineMisc::graphicScale.y);
    m_color = sf::Color(255,0,0);
    m_image.create(1,1,m_color);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);

    m_scale.setX(100);
    m_scale.setY(100);

}
Painter::Painter(const Painter &painter)
{
    this->m_texture = painter.m_texture;
    this->m_image   = painter.m_image;
    this->m_sprite  = painter.m_sprite;
    this->m_color   = painter.m_color;
    this->m_scale   = painter.m_scale;
}
Painter::~Painter()
{

}

void Painter::draw(sf::RenderWindow *window,Vector drawPos)
{
    m_sprite.setPosition(drawPos.getX(), drawPos.getY());
    m_sprite.setScale(m_scale.getX(), m_scale.getY());
    window->draw(m_sprite);
}
void Painter::setScale(Vector scale)
{
    m_scale = scale;
}
void Painter::setScale(double x, double y)
{
    m_scale.setX(x);
    m_scale.setY(y);
}
/*sf::Sprite *Painter::getSprite()
{

}*/
