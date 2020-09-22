#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "collider.h"
#include "vectorFunction.h"

class CircleCollider : public Collider
{
    public:
        CircleCollider();
        CircleCollider(const CircleCollider &collider);
        virtual ~CircleCollider();

        virtual void setSize(const Vector &size);
        virtual void setSize(const double &x, const double &y);
        virtual void setPos(const Vector &pos);
        virtual void setPos(const double &x, const double &y);

        //virtual Vector getSize() const;
        virtual Vector getPos() const;
        virtual Vector getCenter() const;

        //virtual bool collides(const Collider *other) const;
        virtual bool collides(const Collider *other, const Vector &thisVelocity, const Vector &otherVelocity) const;

    protected:

        Vector m_centerOffset; // the mainPos is in the top left corner
                               // this offset moves the center of the circle to the right Pos


    private:
        void setOffset();


        static bool   hasCollisionOnPath(const VectorFunction &func1,
                                         const VectorFunction &func2,
                                         const double &radius1,
                                         const double &radius2,
                                         double &takeDiscriminante,
                                         double &takeDevider);

        // Returns the collisionScalar
        static double getCollisionOnPath(const VectorFunction &func1,
                                         const VectorFunction &func2,
                                         const double &radius1,
                                         const double &radius2);
        static void getDiagnostics(const VectorFunction &func1,
                                   const VectorFunction &func2,
                                   const double &radius1,
                                   const double &radius2,
                                   double &takeDiscriminante,
                                   double &takeDevider);
};
#endif
