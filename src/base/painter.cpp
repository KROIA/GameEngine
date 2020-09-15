#include "painter.h"

vector<Painter*>  Painter::painter_list;

Painter::Painter()
{
    m_ID = Painter::painter_list.size();
    Painter::painter_list.push_back(this);

    skipUpdateSettings = true;
    this->setColor(sf::Color(255,0,0));
    this->setSize(coordinateU(1,1));
    this->setPosition(coordinate(0,0));

    skipUpdateSettings = false;
    this->updateSettings();
}

Painter::~Painter()
{
    //EngineBase::__deleteLater(TYPE_TAG_PAINTER,m_ID);
    //Painter::painter_list.erase(Painter::painter_list.begin()+m_ID);
}

void Painter::setColor(sf::Color color)
{
    m_color = color;
    this->updateSettings();
}
void Painter::setPosition(coordinate pos)
{
    EngineBase::checkOutOfBoarder(pos);
    m_pos = pos;
    this->updateSettings();
}
void Painter::setSize(coordinateU sizeRect)
{
    m_size = sizeRect;
    this->updateSettings();
}

sf::Sprite *Painter::getSprite()
{
    return &m_sprite;
}

void Painter::updateSettings()
{
    if(skipUpdateSettings)
        return;
    m_sprite.setScale(EngineBase::graphicScale.x,EngineBase::graphicScale.y);
    m_image.create(m_size.x,m_size.y,m_color);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setPosition(m_pos.x*EngineBase::graphicScale.x,
                         m_pos.y*EngineBase::graphicScale.y);
    m_sprite.setScale(m_size.x*EngineBase::graphicScale.x,
                      m_size.y*EngineBase::graphicScale.y);



}
