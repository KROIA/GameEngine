#include "cubeCollider.h"

CubeCollider::CubeCollider()
    : Collider()
{
    this->setPos(Vector(-M_PI_4,sqrt(2)));
}

CubeCollider::CubeCollider(const CubeCollider &collider)
    : Collider(collider)
{
    this->m_size = collider.m_size;
    this->m_pos  = collider.m_pos;
}

CubeCollider::~CubeCollider()
{

}

bool CubeCollider::collides(const CubeCollider &other) const
{
    /*double va1x = this->m_pos.getX();
    double va1y = this->m_pos.getY();
    double va2x = this->m_size.getX();
    double va2y = this->m_size.getY();

    double vb1x = other.m_pos.getX();
    double vb1y = other.m_pos.getY();
    double vb2x = other.m_size.getX();
    double vb2y = other.m_size.getY();


    double collisionX = -(va1x*va2y - va1y*va2x + va2x*vb1y - va2y*vb1x)/
                         (va2x*vb2y - va2y*vb2x);

    double collisionY = -(va1x*va2y - va1y*vb2x - va1x*vb2y + va1y*vb2x)/
                         (va2x*vb2y - va2y*vb2x);

    return false;*/

    /*
     *    ax1--------ax2
     *     |          |
     *     |          |
     *     |      bx1-+---------bx2
     *     |       |  |          |
     *    ax3------+-ax4         |
     *             |             |
     *            bx3-----------bx4
     */

    Vector ax1  = this->m_pos;
    Vector ax2  = this->m_pos + Vector(0,this->m_size.getX());
    Vector ax3  = this->m_pos + Vector(M_PI*1.5,this->m_size.getY());
    Vector ax4  = this->m_pos + this->m_size;

    Vector bx1  = other.m_pos;
    Vector bx2  = other.m_pos + Vector(0,other.m_size.getX());
    Vector bx3  = other.m_pos + Vector(M_PI*1.5,other.m_size.getY());
    Vector bx4  = other.m_pos + other.m_size;


    // https://www.geeksforgeeks.org/find-two-rectangles-overlap/
    if(ax1.getX() > bx4.getX() ||
       bx1.getX() > ax4.getX())
        return false;

    if(ax1.getY() > bx4.getY() ||
       bx1.getY() > ax4.getY())
        return false;

    return true;
}
