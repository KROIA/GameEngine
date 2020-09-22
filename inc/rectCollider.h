#ifndef RECTCOLLIDER_H
#define RECTCOLLIDER_H
#include <QDebug>

#include "collider.h"
#include "vectorFunction.h"

//#define _DEBUG_COLLISION

class RectCollider : public Collider
{
    public:
        RectCollider();
        RectCollider(const RectCollider &collider);
        virtual ~RectCollider();

        virtual void setSize(const Vector &size);
        virtual void setSize(const double &x, const double &y);
        virtual void setPos(const Vector &pos);
        virtual void setPos(const double &x, const double &y);

        virtual Vector getCenter() const;

        //virtual bool collides(const Collider *other,Vector &collisionVector) const;
        virtual bool collides(const Collider *other,const Vector &thisVelocity, const Vector &otherVelocity) const;

    protected:

        void updateVecFunc();

        VectorFunction m_Vfunc_left; // Left line of the rect, represented as Vectorfunction
        VectorFunction m_Vfunc_right;
        VectorFunction m_Vfunc_top;
        VectorFunction m_Vfunc_bottom;
    private:


};
#endif
