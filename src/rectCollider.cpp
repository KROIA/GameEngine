#include "rectCollider.h"

RectCollider::RectCollider()
    : Collider()
{
    this->setPos(Vector(-M_PI_4,sqrt(2)));
    this->updateVecFunc();
}

RectCollider::RectCollider(const RectCollider &collider)
    : Collider(collider)
{
 //   this->m_size = collider.m_size;
  //  this->m_pos  = collider.m_pos;
}

RectCollider::~RectCollider()
{

}

void RectCollider::setSize(const Vector &size)
{
    Collider::setSize(size);
    this->updateVecFunc();
}
void RectCollider::setSize(const double &x, const double &y)
{
    Collider::setSize(x,y);
    this->updateVecFunc();
}
void RectCollider::setPos(const Vector &pos)
{
    Collider::setPos(pos);
    this->updateVecFunc();
}
void RectCollider::setPos(const double &x, const double &y)
{
    Collider::setPos(x,y);
    this->updateVecFunc();
}
Vector RectCollider::getCenter() const
{
    std::vector<Vector> list{
        m_Vfunc_top.getPoint(0),
        m_Vfunc_top.getPoint(1),
        m_Vfunc_bottom.getPoint(0),
        m_Vfunc_bottom.getPoint(1)
    };
    return Vector::getAverage(list);
}

//bool RectCollider::collides(const Collider *other,Vector &deltaMove) const
bool RectCollider::collides(const Collider *other,const Vector &thisVelocity, const Vector &otherVelocity) const
{
#define VecCollision

#ifdef VecCollision

    std::vector<Vector> pushOutOfObsticleVectorList;
    RectCollider *_other = (RectCollider*)other;
    bool intersects = false;
    if(m_Vfunc_left.intersects(_other->m_Vfunc_top))
    {
        double x1 = m_Vfunc_left.getIntersectionFactor(_other->m_Vfunc_top);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_top,this->m_Vfunc_left);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.left -X- other.top";
            qDebug() << "  intersects: " << m_Vfunc_left.getIntersection(_other->m_Vfunc_top).toString().c_str() << "\n";
            #endif
            //collisionVector.setX(-1);
           // collisionVector.setY(0);
            intersects = true;
        }
    }
    if(m_Vfunc_left.intersects(_other->m_Vfunc_bottom))
    {
        double x1 = m_Vfunc_left.getIntersectionFactor(_other->m_Vfunc_bottom);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_bottom,this->m_Vfunc_left);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.left -X- other.bottom";
            qDebug() << "  intersects: " << m_Vfunc_left.getIntersection(_other->m_Vfunc_bottom).toString().c_str() << "\n";
            #endif
            //  collisionVector.setX(-1);
            intersects = true;
         //   collisionVector.setX(-1);
         //   collisionVector.setY(0);
        /*    double factor = x1;
            if(factor > 0.5)
                factor = 1-factor; //take the shorter way for pushing the object out of the obsticle
            Vector pushOutVector = m_Vfunc_left.getDirection() * factor;

            pushOutOfObsticleVectorList.push_back(pushOutVector);*/
/*
            // check collision of deltaMoveVector and the other obsticle
            VectorFunction deltaMoveFunc;
            deltaMoveFunc.setBase(m_pos-deltaMove);
            deltaMoveFunc.setDirection(deltaMove);
            if(deltaMoveFunc.intersects(_other->m_Vfunc_bottom))
            {
                double deltaMoveCollisionScalar = deltaMoveFunc.getIntersectionFactor(_other->m_Vfunc_bottom);
                Vector pushBackVector =  deltaMove * -(1-deltaMoveCollisionScalar);
                // pushBackVector: Vector for pushing this object back so it won't collide

            }*/
        }
    }

    if(m_Vfunc_right.intersects(_other->m_Vfunc_top))
    {
        double x1 = m_Vfunc_right.getIntersectionFactor(_other->m_Vfunc_top);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_top,this->m_Vfunc_right);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.right -X- other.top";
            qDebug() << "  intersects: " << m_Vfunc_right.getIntersection(_other->m_Vfunc_top).toString().c_str() << "\n";
            #endif
            intersects = true;
          //  collisionVector.setX(1);
         //   collisionVector.setY(0);
        }
    }
    if(m_Vfunc_right.intersects(_other->m_Vfunc_bottom))
    {
        double x1 = m_Vfunc_right.getIntersectionFactor(_other->m_Vfunc_bottom);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_bottom,this->m_Vfunc_right);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.right -X- other.bottom";
            qDebug() << "  intersects: " << m_Vfunc_right.getIntersection(_other->m_Vfunc_bottom).toString().c_str() << "\n";
            #endif
            intersects = true;
         //   collisionVector.setX(1);
          //  collisionVector.setY(0);
        }
    }

    if(m_Vfunc_top.intersects(_other->m_Vfunc_left))
    {
        double x1 = m_Vfunc_top.getIntersectionFactor(_other->m_Vfunc_left);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_left,this->m_Vfunc_top);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.left -X- other.top";
            qDebug() << "  intersects: " << m_Vfunc_left.getIntersection(_other->m_Vfunc_top).toString().c_str() << "\n";
            #endif
            //collisionVector.setX(-1);
           // collisionVector.setY(0);
            intersects = true;
        }
    }
    if(m_Vfunc_top.intersects(_other->m_Vfunc_right))
    {
        double x1 = m_Vfunc_top.getIntersectionFactor(_other->m_Vfunc_right);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_right,this->m_Vfunc_top);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.left -X- other.bottom";
            qDebug() << "  intersects: " << m_Vfunc_left.getIntersection(_other->m_Vfunc_bottom).toString().c_str() << "\n";
            #endif
            //  collisionVector.setX(-1);
            intersects = true;
         //   collisionVector.setX(-1);
         //   collisionVector.setY(0);
        /*    double factor = x1;
            if(factor > 0.5)
                factor = 1-factor; //take the shorter way for pushing the object out of the obsticle
            Vector pushOutVector = m_Vfunc_left.getDirection() * factor;

            pushOutOfObsticleVectorList.push_back(pushOutVector);*/
/*
            // check collision of deltaMoveVector and the other obsticle
            VectorFunction deltaMoveFunc;
            deltaMoveFunc.setBase(m_pos-deltaMove);
            deltaMoveFunc.setDirection(deltaMove);
            if(deltaMoveFunc.intersects(_other->m_Vfunc_bottom))
            {
                double deltaMoveCollisionScalar = deltaMoveFunc.getIntersectionFactor(_other->m_Vfunc_bottom);
                Vector pushBackVector =  deltaMove * -(1-deltaMoveCollisionScalar);
                // pushBackVector: Vector for pushing this object back so it won't collide

            }*/
        }
    }

    if(m_Vfunc_bottom.intersects(_other->m_Vfunc_left))
    {
        double x1 = m_Vfunc_bottom.getIntersectionFactor(_other->m_Vfunc_left);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_left,this->m_Vfunc_bottom);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.right -X- other.top";
            qDebug() << "  intersects: " << m_Vfunc_right.getIntersection(_other->m_Vfunc_top).toString().c_str() << "\n";
            #endif
            intersects = true;
          //  collisionVector.setX(1);
         //   collisionVector.setY(0);
        }
    }
    if(m_Vfunc_bottom.intersects(_other->m_Vfunc_right))
    {
        double x1 = m_Vfunc_bottom.getIntersectionFactor(_other->m_Vfunc_right);
        double x2 = VectorFunction::getIntersectionFactor(_other->m_Vfunc_right,this->m_Vfunc_bottom);
        if(x1 >= 0 && x1 <= 1 &&
           x2 >= 0 && x2 <= 1)
        {
            #ifdef _DEBUG_COLLISION
            qDebug() << "collision: this.right -X- other.bottom";
            qDebug() << "  intersects: " << m_Vfunc_right.getIntersection(_other->m_Vfunc_bottom).toString().c_str() << "\n";
            #endif
            intersects = true;
         //   collisionVector.setX(1);
          //  collisionVector.setY(0);
        }
    }
    return intersects;
#else
   /* double va1x = this->m_pos.getX();
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

    Vector bx1  = other->getPos();
    Vector bx2  = other->getPos() + Vector(0,other->getSize().getX());
    Vector bx3  = other->getPos() + Vector(M_PI*1.5,other->getSize().getY());
    Vector bx4  = other->getPos() + other->getSize();


    // https://www.geeksforgeeks.org/find-two-rectangles-overlap/
    if(ax1.getX() > bx4.getX() ||
       bx1.getX() > ax4.getX())
        return false;

    if(ax1.getY() > bx4.getY() ||
       bx1.getY() > ax4.getY())
        return false;

    return true;
#endif
}


void RectCollider::updateVecFunc()
{
    /*            (0|0)
     *              +  .
     *              .. .    .base
     *              . .base      .
     *               . .  m_Vfunc_top .
     *           base.  +--------------->+
     *                . |      .         |
     *                . |        .base   |
     *      m_Vfunc_left|          .     |m_Vfunc_right
     *                 .|            .   |
     *                  V              . V
     *                  +--------------->+
     *                    m_Vfunc_bottom
     */




    m_Vfunc_left.setBase(this->m_pos);
    Vector leftDir; leftDir.setX(0); leftDir.setY(this->m_size.getY());
    m_Vfunc_left.setDirection(leftDir);

    Vector rightBase; rightBase.setX(this->m_pos.getX()+this->m_size.getX()); rightBase.setY(this->m_pos.getY());
    m_Vfunc_right.setBase(rightBase);
    Vector rightDir; rightDir.setX(0); rightDir.setY(this->m_size.getY());
    m_Vfunc_right.setDirection(rightDir);

    m_Vfunc_top.setBase(this->m_pos);
    Vector topDir; topDir.setX(this->m_size.getX()); topDir.setY(0);
    m_Vfunc_top.setDirection(topDir);

    Vector bottomBase; bottomBase.setX(this->m_pos.getX()); bottomBase.setY(this->m_pos.getY()+this->m_size.getY());
    m_Vfunc_bottom.setBase(bottomBase);
    Vector bottomDir; bottomDir.setX(this->m_size.getX()); bottomDir.setY(0);
    m_Vfunc_bottom.setDirection(bottomDir);

 /*   qDebug() << "ColliderPoints: ";
    qDebug() << "Vtop    = ( "<<m_Vfunc_top.getPoint(0).getX()<<" / "<<m_Vfunc_top.getPoint(0).getY()<<" ) --> ( "<<m_Vfunc_top.getPoint(1).getX()<<" / "<<m_Vfunc_top.getPoint(1).getY()<<" )";
    qDebug() << "Vright  = ( "<<m_Vfunc_right.getPoint(0).getX()<<" / "<<m_Vfunc_right.getPoint(0).getY()<<" ) --> ( "<<m_Vfunc_right.getPoint(1).getX()<<" / "<<m_Vfunc_right.getPoint(1).getY()<<" )";
    qDebug() << "Vbottom = ( "<<m_Vfunc_bottom.getPoint(0).getX()<<" / "<<m_Vfunc_bottom.getPoint(0).getY()<<" ) --> ( "<<m_Vfunc_bottom.getPoint(1).getX()<<" / "<<m_Vfunc_bottom.getPoint(1).getY()<<" )";
    qDebug() << "Vleft   = ( "<<m_Vfunc_left.getPoint(0).getX()<<" / "<<m_Vfunc_left.getPoint(0).getY()<<" ) --> ( "<<m_Vfunc_left.getPoint(1).getX()<<" / "<<m_Vfunc_left.getPoint(1).getY()<<" )";
    qDebug() << "end";
*/


}
