#include "collider.h"

Collider::Collider()
{
    this->setPos(Vector(-M_PI_4,sqrt(2)));
    this->setSize(1,1);
}

Collider::Collider(const Collider &collider)
{
    this->m_size = collider.m_size;
    this->m_pos  = collider.m_pos;
}

Collider::~Collider()
{

}


void Collider::setSize(const Vector &size)
{
    m_size = size;
}
void Collider::setSize(const double &x, const double &y)
{
    m_size.setX(x);
    m_size.setY(y);
}

void Collider::setPos(const Vector &pos)
{
    m_pos = pos;
}
void Collider::setPos(const double &x, const double &y)
{
    m_pos.setX(x);
    m_pos.setY(y);
}

Vector Collider::getSize() const
{
    return m_size;
}

Vector Collider::getPos() const
{
    return m_pos;
}
Vector Collider::getCenter() const
{
    return Vector(0,0);
}

//bool Collider::collides(const Collider *other,Vector &deltaMove) const
bool Collider::collides(const Collider *other,const Vector &thisVelocity, const Vector &otherVelocity) const
{
    return false;
}
