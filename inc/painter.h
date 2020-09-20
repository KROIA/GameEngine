#ifndef PAINTER_H
#define PAINTER_H

#include <SFML/Graphics.hpp>
#include "vector.h"

class Painter
{
    public:
        Painter();
        Painter(const Painter &painter);
        virtual ~Painter();

        virtual void draw(sf::RenderWindow *window,Vector drawPos);


        virtual void setScale(Vector scale);
        virtual void setScale(double x, double y);
       // virtual sf::Sprite *getSprite();

    protected:
        //Graphics
        sf::Texture m_texture;
        sf::Image   m_image;
        sf::Sprite  m_sprite;
        sf::Color   m_color;
        Vector      m_scale;
    private:

};

#endif
