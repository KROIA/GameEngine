#ifndef GRAVITYCONTROLLER_H
#define GRAVITYCONTROLLER_H

#include "controller.h"

class GravityController : public Controller
{
    public:
        GravityController();
        GravityController(double force);
        GravityController(const GravityController &controller);
        virtual ~GravityController();

        virtual void setForce(double force);
        virtual void setForceVector(Vector force);

        virtual void tick(double timeInterval,b2Body *body);



    protected:

    private:
        Vector m_gravityDeltaV;
};
#endif
