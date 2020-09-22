#include "circleCollider.h"

CircleCollider::CircleCollider()
{
    this->setPos(0,0);
    this->setSize(1,0);
}
CircleCollider::CircleCollider(const CircleCollider &collider)
    : Collider(collider)
{
    this->m_centerOffset = collider.m_centerOffset;
}
CircleCollider::~CircleCollider()
{

}

void CircleCollider::setSize(const Vector &size)
{
    Collider::setSize(size*0.5);
    this->setOffset();
}
void CircleCollider::setSize(const double &x, const double &y)
{
    Collider::setSize(x/2,y/2);
    this->setOffset();
}
void CircleCollider::setPos(const Vector &pos)
{
    Collider::setPos(pos);
    this->setOffset();
}
void CircleCollider::setPos(const double &x, const double &y)
{
    Collider::setPos(x,y);
    this->setOffset();
}

/*Vector CircleCollider::getSize() const
{

}*/
Vector CircleCollider::getPos() const
{
    return this->m_pos - m_centerOffset;
}


bool CircleCollider::collides(const Collider *other, const Vector &thisVelocity, const Vector &otherVelocity) const
{
    CircleCollider *_other = (CircleCollider*)other;
    VectorFunction func1;
    VectorFunction func2;
    func1.setBase(this->m_pos);
    func1.setDirection(thisVelocity);

    func2.setBase(_other->m_pos);
    func2.setDirection(otherVelocity);

    double discriminante;
    double divider;

    if(CircleCollider::hasCollisionOnPath(func1,func2,this->m_size.getLength(),_other->m_size.getLength(),discriminante,divider))
    {
        double scalar = CircleCollider::getCollisionOnPath(func1,func2,this->m_size.getLength(),_other->m_size.getLength());
        if(scalar <=1 && scalar >= 0)
        {
            CircleCollider::getDiagnostics(func1,func2,this->m_size.getLength(),_other->m_size.getLength(),discriminante,divider);
            return true;
        }
    }
    return false;
}

Vector CircleCollider::getCenter() const
{
    return this->m_pos;
}

void CircleCollider::setOffset()
{
    m_centerOffset.setAngle(Vector::radToDeg(45));
    m_centerOffset.setLength(this->m_size.getLength());
    this->m_pos += m_centerOffset;
}

bool   CircleCollider::hasCollisionOnPath(const VectorFunction &func1,
                                          const VectorFunction &func2,
                                          const double &radius1,
                                          const double &radius2,
                                          double &takeDiscriminante,
                                          double &takeDevider)
{
    double ov1x = func1.getBase().getX();
    double ov1y = func1.getBase().getY();
    double v1x  = func1.getDirection().getX();
    double v1y  = func1.getDirection().getY();

    double ov2x = func2.getBase().getX();
    double ov2y = func2.getBase().getY();
    double v2x  = func2.getDirection().getX();
    double v2y  = func2.getDirection().getY();

    double length = radius1 + radius2;

    // Things get complicated...
    takeDiscriminante = pow(length,2)*(pow(v1x,2)-2*v1x*v2x+pow(v1y,2)-2*v1y*v2y+pow(v2x,2)+pow(v2y,2))-pow(ov1x,2)*(pow(v1y,2)-2*v1y*v2y+pow(v2y,2))+2*ov1x*(ov1y*(v1x-v2x)+ov2x*(v1y-v2y)-ov2y*(v1x-v2x))*(v1y-v2y)-pow(ov1y,2)*(pow(v1x,2)-2*v1x*v2x+pow(v2x,2))-2*ov1y*(ov2x*(v1y-v2y)-ov2y*(v1x-v2x))*(v1x-v2x)-pow(ov2x,2)*(pow(v1y,2)-2*v1y*v2y+pow(v2y,2))+2*ov2x*ov2y*(v1x-v2x)*(v1y-v2y)-pow(ov2y,2)*(pow(v1x,2)-2*v1x*v2x+pow(v2x,2));
    takeDevider = (pow(v1x,2)-2*v1x*v2x+pow(v1y,2)-2*v1y*v2y+pow(v2x,2)+pow(v2y,2));


    if(takeDiscriminante < 0 || takeDevider == 0)
    {
        // no Collision
        //qDebug() << "no result: discriminante = "<<discriminante << "\tdivider = "<<divider;
        return false;
    }
    return true;
}
double CircleCollider::getCollisionOnPath(const VectorFunction &func1,
                                          const VectorFunction &func2,
                                          const double &radius1,
                                          const double &radius2)
{
    double ov1x = func1.getBase().getX();
    double ov1y = func1.getBase().getY();
    double v1x  = func1.getDirection().getX();
    double v1y  = func1.getDirection().getY();

    double ov2x = func2.getBase().getX();
    double ov2y = func2.getBase().getY();
    double v2x  = func2.getDirection().getX();
    double v2y  = func2.getDirection().getY();

    double t1 = 0;
    double t2 = 0;
    // Things get complicated...
    double discriminante;
    double divider;

    if(CircleCollider::hasCollisionOnPath(func1,func2,radius1,radius2,discriminante,divider))
    {
        t1=((  sqrt(discriminante)-ov1x*(v1x-v2x)-ov1y*(v1y-v2y)+ov2x*(v1x-v2x)+ov2y*(v1y-v2y))   /  divider);
        t2=((-(sqrt(discriminante)+ov1x*(v1x-v2x)+ov1y*(v1y-v2y)-ov2x*(v1x-v2x)-ov2y*(v1y-v2y)))  /  divider);
    }
    else
    {
        qDebug() << "Warning: CircleCollider::getCollisionOnPath(...) no collision";
    }
    if(t1 < t2)
        return t1;
    return t2;
}

void CircleCollider::getDiagnostics(const VectorFunction &func1,
                                   const VectorFunction &func2,
                                   const double &radius1,
                                   const double &radius2,
                                   double &takeDiscriminante,
                                   double &takeDevider)
{

    double ov1x = func1.getBase().getX();
    double ov1y = func1.getBase().getY();
    double v1x  = func1.getDirection().getX();
    double v1y  = func1.getDirection().getY();

    double ov2x = func2.getBase().getX();
    double ov2y = func2.getBase().getY();
    double v2x  = func2.getDirection().getX();
    double v2y  = func2.getDirection().getY();


    double t1 = 0;
    double t2 = 0;

    Vector Vr1(0,radius1);
    Vector Vr2(0,radius2);

    double length = radius1 + radius2;

    t1=((  sqrt(takeDiscriminante)-ov1x*(v1x-v2x)-ov1y*(v1y-v2y)+ov2x*(v1x-v2x)+ov2y*(v1y-v2y))   /  takeDevider);
    t2=((-(sqrt(takeDiscriminante)+ov1x*(v1x-v2x)+ov1y*(v1y-v2y)-ov2x*(v1x-v2x)-ov2y*(v1y-v2y)))  /  takeDevider);

    qDebug() << "Function1:\tOV1x\tOV1y \t\tFunction2:\tOV2x\tOV2y";
    qDebug() << "\t"<<0 << "\t" << 0 << "\t\t\t" << 0 << "\t" << 0;
    qDebug() << "\t"<<func1.getBase().getX() << "\t" << func1.getBase().getY() << "\t\t\t" << func2.getBase().getX() << "\t" << func2.getBase().getY();
    qDebug() << "\t"<<func1.getPoint(1).getX() << "\t"<<func1.getPoint(1).getY() << "\t\t\t"<<func2.getPoint(1).getX() << "\t"<<func2.getPoint(1).getY();
    qDebug() << "";


    qDebug() << "t1 = "<< t1 << "\t diskriminante = "<<takeDiscriminante;
    qDebug() << "t2 = "<< t2 << "\t divisor = "<<takeDevider;
    qDebug() << "minDistance: \t"<<length;
    qDebug() << "t\t\tX1\tY1\t\tX2\tY2\t\tdistance\t\t";

    double deltaIterator = 0.025;
    double t = 0.2;

    std::vector<std::vector<double> > Vr1List;
    std::vector<std::vector<double> > Vr2List;
    std::vector<std::vector<double> > VdRestList;

    for(int i=0; i<30; i++)
    {

        Vector fPos1 = func1.getPoint(t);
        Vector fPos2 = func2.getPoint(t);
        Vector Vd = fPos2 - fPos1;


        Vr1.setAngle(Vd.getAngle());
        Vr2.setAngle(M_PI+Vd.getAngle());

        Vector VdRest = Vd - Vr1 + Vr2;

        qDebug() << t << "\t\t" <<
                    fPos1.getX() << "\t"<< fPos1.getY() << "\t\t" <<
                    fPos2.getX() << "\t"<< fPos2.getY() << "\t\t" <<
                    VdRest.getLength();

        Vr1List.push_back({(fPos1).getX(),(fPos1).getY()});
        Vr1List.push_back({(fPos1+Vr1).getX(),(fPos1+Vr1).getY()});

        Vr2List.push_back({(fPos2).getX(),(fPos2).getY()});
        Vr2List.push_back({(fPos2+Vr2).getX(),(fPos2+Vr2).getY()});

        VdRestList.push_back({(fPos1+Vr1).getX(),(fPos1+Vr1).getY()});
        VdRestList.push_back({(fPos1+Vr1+VdRest).getX(),(fPos1+Vr1+VdRest).getY()});

        t+=deltaIterator;

    }
    qDebug() << "Vr1x\tVr1y\tVr2x\tVr2y\tVdRestX\tVdRestY";
    for(unsigned int i=0; i<Vr1List.size(); i++)
    {
        qDebug() << Vr1List[i][0]    << "\t"<<Vr1List[i][1] << "\t" <<
                    Vr2List[i][0]    << "\t"<<Vr2List[i][1] << "\t" <<
                    VdRestList[i][0] << "\t"<<VdRestList[i][1];
    }

    qDebug() << "vectortest end";
}
