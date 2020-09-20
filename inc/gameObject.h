#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vector.h"
#include "collider.h"
#include "controller.h"
#include "painter.h"

class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();

        void addCollider(Collider collider);
        void addController(Controller* controller);
        void addPainter(Painter painter);

        virtual void tick(double timeInterval);
        virtual void draw(sf::RenderWindow *window);



    protected:
        std::vector<Collider>    m_colliderList;
        std::vector<Controller*> m_controllerList;
        std::vector<Painter>     m_painterList;


    private:
       // Controller m_controller;
        Painter m_painter;

        Vector m_pos;
        Vector m_lastVel;
};
#endif
