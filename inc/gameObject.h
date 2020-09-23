#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "vector.h"
#include "collider.h"
#include "controller.h"
#include "painter.h"

#include "box2d/box2d.h"

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

        virtual void movePos(Vector delta);
        virtual void setPos(Vector pos);
        virtual void setPos(double x, double y);
        virtual Vector getPos() const;

        virtual void setSize(Vector size);
        virtual void setSize(double x, double y);
        virtual Vector getSize() const;

        virtual void setVelocity(Vector vel);
        virtual Vector getVelocity();

        virtual void setStatic(bool enable);
        virtual void setColor(sf::Color color);

        virtual void setDensity(double density);
        virtual void createBody(b2World *world);

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
        double m_density;

        bool m_isStatic;


        // box2d
        b2BodyDef m_bodyDef;
        b2Body*   m_body;
        b2PolygonShape m_dynamicBox;
        b2FixtureDef m_fixtureDef;
};
#endif
