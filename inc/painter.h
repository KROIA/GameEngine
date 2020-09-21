#ifndef PAINTER_H
#define PAINTER_H

#include <SFML/Graphics.hpp>
#include "vector.h"

class Painter
{
    public:
        Painter();
        Painter(const std::string &texturePath);
        Painter(const std::string &texturePath,double width, double height);
        Painter(const Painter &painter);
        virtual ~Painter();

        virtual void draw(sf::RenderWindow *window,Vector drawPos);

        virtual void setColor(const sf::Color &color);
        virtual void loadFromFile(const std::string &texturePath);



        virtual void setSize(Vector size);
        virtual void setSize(double x, double y);
        virtual sf::Sprite getSprite() const;

    protected:


        //Graphics
        sf::Texture *m_texture;
        sf::Image   *m_image;
        sf::Sprite  *m_sprite;
        sf::Color   m_color;
        Vector      m_size;
    private:

};

#endif
