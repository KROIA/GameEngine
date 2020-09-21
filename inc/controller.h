#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "vector.h"
#include "timer.h"
#include <QDebug>

class Controller
{
    public:
        Controller();
        Controller(const Controller &controller);
        virtual ~Controller();

        virtual void tick(double timeInterval); // calculate next physics step

        virtual void setVelocity(const Vector &vel);
        virtual Vector getVelocity() const;

        virtual void setAcceleration(const Vector &acc);
        virtual Vector getAcceleration() const;

        virtual void addVelocity(const Vector &vel);
        virtual void addAcceleration(const Vector &acc);


    protected:

        Vector m_velocity;
        Vector m_acceleration;

        std::vector<Vector> m_velocityList;
        std::vector<Vector> m_accelerationList;

    private:

};
#endif
