#ifndef GRAVITYCONTROLLER_H
#define GRAVITYCONTROLLER_H

#include "controller.h"

class GravityController : public Controller
{
    public:
        GravityController();
        GravityController(const GravityController &controller);
        virtual ~GravityController();

        virtual void tick(double timeInterval);



    protected:

    private:
        Vector m_gravityDeltaV;
};
#endif
