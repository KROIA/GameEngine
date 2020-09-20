#ifndef COLLIDER_H
#define COLLIDER_H

#include "vector.h"

class Collider
{
    public:
        Collider();
        Collider(const Collider &collider);
        virtual ~Collider();

        virtual void setSize(const Vector &size);
        virtual void setSize(const double &x, const double &y);
        virtual void setPos(const Vector &pos);
        virtual void setPos(const double &x, const double &y);

        virtual Vector getSize() const;
        virtual Vector getPos() const;

    protected:
        Vector m_size;
        Vector m_pos;
    private:

};
#endif
