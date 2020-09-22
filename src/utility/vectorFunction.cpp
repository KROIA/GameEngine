#include "vectorFunction.h"

VectorFunction::VectorFunction()
{
    setBase(0,0);
    setDirection(1,0);
}
VectorFunction::VectorFunction(const VectorFunction &other)
{
    this->m_base      = other.m_base;
    this->m_direction = other.m_direction;
}
VectorFunction::~VectorFunction()
{

}

void VectorFunction::setBase(Vector base)
{
    this->m_base = base;
}
void VectorFunction::setBase(double x, double y)
{
    this->m_base.setX(x);
    this->m_base.setY(y);
}
Vector VectorFunction::getBase() const
{
    return this->m_base;
}

void VectorFunction::setDirection(Vector direction)
{
    this->m_direction = direction;
   /* if(this->m_direction.getLength() == 0)
    {
        qDebug() << "Error: VectorFunction::setDirection(Vector direction): direction has no length";
    }*/
}
void VectorFunction::setDirection(double x, double y)
{
    this->m_direction.setX(x);
    this->m_direction.setY(y);
   /* if(this->m_direction.getLength() == 0)
    {
        qDebug() << "Error: VectorFunction::setBase(double x, double y): direction has no length";
    }*/
}
Vector VectorFunction::getDirection() const
{
    return this->m_direction;
}

Vector VectorFunction::getPoint(double x) const
{
    return VectorFunction::getPoint(*this,x);
}

bool   VectorFunction::intersects(const VectorFunction &other) const
{
    return VectorFunction::intersects(*this,other);
}
double VectorFunction::getIntersectionFactor(const VectorFunction &other) const
{
    return VectorFunction::getIntersectionFactor(*this,other);
     /*double x = 0; // intersectionMultiplyer for this VectorFunction

     double Vx1 = other.m_base.getX();
     double Vy1 = other.m_base.getY();

     double Vx2 = other.m_direction.getX();
     double Vy2 = other.m_direction.getY();

     double Vx3 = this->m_base.getX();
     double Vy3 = this->m_base.getY();

     double Vx4 = this->m_direction.getX();
     double Vy4 = this->m_direction.getY();



     if(!this->intersects(other))
     {
         qDebug() << "Error: VectorFunction::getIntersectionFactor(const VectorFunction &other): no intersection!";
         return x;
     }
     x = (Vx2 * (Vy3 - Vy1) - Vy2 * (Vx3 - Vx1)) /
             (Vy2 * Vx4 + Vx2 * Vy4);

     return x;*/
}
Vector VectorFunction::getIntersection(const VectorFunction &other) const
{
    return VectorFunction::getIntersection(*this,other);
}


Vector VectorFunction::getPoint(const VectorFunction &func,double x)
{
    return func.m_base + func.m_direction * x;
}
bool   VectorFunction::intersects(const VectorFunction &first,const VectorFunction &second)
{

   /*if(first.m_direction.getY() * second.m_direction.getX() +
       first.m_direction.getX() * second.m_direction.getY()
            == 0)*/
    if(Vector::getAngle(first.m_direction,second.m_direction) == 0)
    {
        // Richtungsvectoren sind parallel
        return false;
    }
    return true;
}
double VectorFunction::getIntersectionFactor(const VectorFunction &first,const VectorFunction &second)
{
     double x = 0; // intersectionMultiplyer for this VectorFunction

     double Vx1 = first.m_base.getX();
     double Vy1 = first.m_base.getY();

     double Vx2 = first.m_direction.getX();
     double Vy2 = first.m_direction.getY();

     double Vx3 = second.m_base.getX();
     double Vy3 = second.m_base.getY();

     double Vx4 = second.m_direction.getX();
     double Vy4 = second.m_direction.getY();







     if(!VectorFunction::intersects(first,second))
     {
         qDebug() << "Error: VectorFunction::getIntersectionFactor(const VectorFunction &first,const VectorFunction &second): no intersection!";
         return x;
     }
     x = (Vx4 * Vy1 - Vx4 * Vy3 - Vy4 * Vx1 + Vy4 * Vx3)/
             (Vy4 * Vx2 - Vx4 * Vy2);
     /*x = (Vx2 * (Vy3 - Vy1) - Vy2 * (Vx3 - Vx1)) /
             (Vy2 * Vx4 + Vx2 * Vy4);*/

     return x;
}

Vector VectorFunction::getIntersection(const VectorFunction &first,const VectorFunction &second)
{
    if(!VectorFunction::intersects(first,second))
    {
        qDebug() << "Error: VectorFunction::getIntersection(const VectorFunction &first,const VectorFunction &second): no intersection!";
        return Vector(0,0);
    }
    return VectorFunction::getPoint(first,VectorFunction::getIntersectionFactor(first,second));
}
