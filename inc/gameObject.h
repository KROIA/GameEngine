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

        void addCollider(Collider *collider);
        void addController(Controller *controller);
        void addPainter(Painter *painter);

        virtual void move(double timeInterval);
        virtual bool checkCollision(GameObject *other);
        virtual bool checkCollision(std::vector<GameObject*> others);
        virtual void draw(sf::RenderWindow *window);


        virtual void setPos(Vector pos);
        virtual void setPos(double x, double y);
        virtual Vector getPos() const;

        virtual void setSize(Vector size);
        virtual void setSize(double x, double y);
        virtual Vector getSize() const;

        virtual void setVelocity(Vector vel);



    protected:
        std::vector<Collider*>   m_colliderList;
        std::vector<Controller*> m_controllerList;
        std::vector<Painter*>    m_painterList;


    private:
       // Controller m_controller;
        Vector  m_size;


        Vector m_pos;
        Vector m_lastPos;
        Vector m_lastVelocity;
        Vector m_velocity;
};
#endif
