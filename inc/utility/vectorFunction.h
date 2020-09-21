#ifndef VECTORFUNCTION_H
#define VECTORFUNCTION_H

#include "vector.h"

class VectorFunction
{
    public:
        VectorFunction();
        VectorFunction(const VectorFunction &other);
        virtual ~VectorFunction();

        void setBase(Vector base);
        void setBase(double x, double y);
        Vector getBase() const;

        void setDirection(Vector direction);
        void setDirection(double x, double y);
        Vector getDirection() const;

        Vector getPoint(double x) const;

        bool   intersects(const VectorFunction &other) const;
        double getIntersectionFactor(const VectorFunction &other) const;
        Vector getIntersection(const VectorFunction &other) const;

        static Vector getPoint(const VectorFunction &func,double x);
        static bool   intersects(const VectorFunction &first,const VectorFunction &second);
        static double getIntersectionFactor(const VectorFunction &first,const VectorFunction &second);
        static Vector getIntersection(const VectorFunction &first,const VectorFunction &second);


    protected:
        Vector m_base;
        Vector m_direction;


    private:


};
#endif // VECTORFUNCTION_H
