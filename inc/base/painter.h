#ifndef PAINTER_H
#define PAINTER_H

#include "EngineBase.h"

class Painter
{
    public:
        Painter();

        ~Painter();

        void setColor(sf::Color color);
        void setPosition(coordinate pos);
        void setSize(coordinateU sizeRect);

        sf::Sprite *getSprite();

        void updateSettings();

        static vector<Painter*>  painter_list;
    private:
        unsigned int m_ID; // index of instance.
        bool skipUpdateSettings;

        coordinate m_pos;
        coordinateU m_size;

        //Graphics
        sf::Texture m_texture;
        sf::Image   m_image;
        sf::Sprite  m_sprite;
        sf::Color   m_color;

};
#endif // PAINTER_H
