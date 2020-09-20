#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "EngineMisc.h"

class Controller
{
    public:
        Controller();

        ~Controller();

        void update();

        void gravity(bool enable);
        bool gravity();

        void setVelocity(Velocity vel);
        Velocity getVelocity();

        void setMass(double mass);
        double getMass();

        void move(coordinate deltaPos);

        void setPosition(coordinate pos);
        coordinate getPosition();

        void setSize(coordinateU size);
        coordinateU getSize();

        void setEvent_onMove(GameObject *obj,void (GameObject::*p_func)(Controller*,coordinate));
        void sendEvent_onMove(coordinate deltaPos);


        static vector<Controller*>  controller_list;
    private:
        unsigned int m_ID; // index of instance.

        // Physic settings
        bool m_enable_gravity;
        Velocity m_velocity;
        double m_mass; //Kg
        coordinate m_pos;
        coordinateU m_size;

        //coordinate m_lastPos;

        // stacked tasks
        vector<coordinate> m_moveList; // if there are multiple moves per tick to handle
        void applyMoveList();

        // Events execution
        GameObject *m_p_obj;
        void (GameObject::*m_p_func_onMove)(Controller*,coordinate);
};
#endif // CONTROLLER_H
