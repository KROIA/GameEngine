#ifndef PHYSICS_H
#define PHYSICS_H

#include "EngineMisc.h"
#include "collider.h"
#include "controller.h"
#include <SFML/Graphics/Rect.hpp>
#include <math.h>

namespace Physics
{
    namespace Constants
    {
        extern const Force gForce;
        extern const Velocity gVelocity;
    }


    extern bool isCollided(Collider *objA,Collider *objB);

    extern void applyForce(Controller *controller, Force force);
    extern void applyGravity(Controller *controller);

    extern Velocity velocity_add(Velocity vel1,Velocity vel2);



};
#endif // PHYSICS_H
