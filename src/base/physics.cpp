#include "physics.h"

namespace Physics
{
    namespace Constants
    {
        //double const gForce = -9.81;
        const Force gForce{.force = -9.81,.direction = coordinateF(0,-1)};
        const Velocity gVelocity{.velocity = gForce.force,};
    }

    bool isCollided(Collider *objA,Collider *objB)
    {
        sf::Rect<long> rectA(objA->getPos().x,objA->getPos().y,
                                     objA->getSize().x,objA->getSize().y);

        sf::Rect<long> rectB(objB->getPos().x,objB->getPos().y,
                                     objB->getSize().x,objB->getSize().y);
        bool ret = rectA.intersects(rectB);
        if(ret)
        {
            qDebug() << "collision";
        }
        return ret;
    }

    void applyForce(Controller *controller, Force force)
    {
        // 1N = 1kg*m/s^2   --> m/s^2 = 1N/kg
        Velocity acceleration;
        acceleration.direction = force.direction;
        acceleration.velocity = EngineBase::updateDurationTime * force.force/controller->getMass();

        controller->setVelocity(velocity_add(controller->getVelocity(),acceleration));
    }
    void applyGravity(Controller *controller)
    {
        if(controller->gravity())
        {
            applyForce(controller,Constants::gForce);
        }
    }


    Velocity velocity_add(Velocity vel1,Velocity vel2)
    {
        Velocity result{.velocity = 0,.direction=coordinateF(0,0)};
        if(vel1.velocity == 0)
            return vel2;
        else if(vel2.velocity == 0)
            return vel1;
        result.direction.x = vel1.direction.x*vel1.velocity + vel2.direction.x*vel2.velocity;
        result.direction.y = vel1.direction.y*vel1.velocity + vel2.direction.y*vel2.velocity;

        result.velocity = 1;
        return result;
    }
};
