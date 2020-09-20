#ifndef CUBECOLLIDER_H
#define CUBECOLLIDER_H
#include <QDebug>

#include "collider.h"

class CubeCollider : public Collider
{
    public:
        CubeCollider();
        CubeCollider(const CubeCollider &collider);
        virtual ~CubeCollider();

        virtual bool collides(const CubeCollider &other) const;

    private:
};
#endif
