#ifndef COLLIDER_H
#define COLLIDER_H

#include "EngineMisc.h"

class Collider
{
    public:
        Collider();
        Collider(const Collider &original);

        ~Collider();


        void setPosition(coordinate pos);
        void setSize(coordinateU size);

        coordinate getPos();
        coordinateU getSize();


        void setEvent_onCollision(GameObject *obj,void (GameObject::*p_func)(Collider *));

        void sendEvent_onCollision();

        static vector<Collider*>  collider_list;
    private:
        unsigned int m_ID; // index of instance.



        coordinate m_pos;
        coordinateU m_size;

        // Events execution
        GameObject *m_p_obj;
        void (GameObject::*m_p_func_onCollision)(Collider *);


};
#endif // COLLIDER_H
