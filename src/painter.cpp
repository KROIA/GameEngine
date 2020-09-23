#include "painter.h"


Painter::Painter()
{
    m_texture   = new sf::Texture();
    m_image     = new sf::Image();
    m_sprite    = new sf::Sprite();

    setColor(sf::Color(255,0,0));
    m_size.setX(100);
    m_size.setY(100);
   // m_sprite->setScale(m_size.getX(), m_size.getY());
}
Painter::Painter(const std::string &texturePath)
{
    Painter();
    this->loadFromFile(texturePath);
}
Painter::Painter(const std::string &texturePath,double width, double height)
{
    Painter((std::string&)texturePath);
    this->setSize(width,height);
}
Painter::Painter(const Painter &painter)
{
    this->m_texture = painter.m_texture;
    this->m_image   = painter.m_image;
    this->m_sprite  = painter.m_sprite;
    this->m_color   = painter.m_color;
    this->m_size    = painter.m_size;
}
Painter::~Painter()
{
    delete m_texture;
    delete m_image;
    delete m_sprite;
}
void Painter::setColor(const sf::Color &color)
{
    m_color = color;
    m_image->create(1,1,m_color);
    m_texture->loadFromImage(*m_image);
    m_sprite->setTexture(*m_texture);
}
void Painter::loadFromFile(const std::string &texturePath)
{

    m_texture->loadFromFile(texturePath);
    delete m_sprite;
    m_sprite = new sf::Sprite();
    m_sprite->setTexture(*m_texture);

    this->setSize(m_size);
}
void Painter::draw(sf::RenderWindow *window,Vector drawPos)
{
    m_sprite->setPosition(drawPos.getX(), -drawPos.getY());
    sf::Vector2u windwoSize = window->getSize();
    m_sprite->setScale((m_size.getX()/m_texture->getSize().x)/**(double)windwoSize.y/(double)windwoSize.x*/,
                       (m_size.getY()/m_texture->getSize().y)/**(double)windwoSize.x/(double)windwoSize.y*/);
    window->draw(*m_sprite);
}
void Painter::setSize(Vector size)
{
    m_size = size;
    //m_sprite->setScale(m_size.getX()/m_texture->getSize().x,m_size.getY()/m_texture->getSize().y);
}
void Painter::setSize(double x, double y)
{
    m_size.setX(x);
    m_size.setY(y);
    //m_sprite->setScale(m_size.getX()/m_texture->getSize().x,m_size.getY()/m_texture->getSize().y);
}



sf::Sprite Painter::getSprite() const
{
    return *m_sprite;
}
