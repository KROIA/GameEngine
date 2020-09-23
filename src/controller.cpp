#include "controller.h"

Controller::Controller()
{
    m_velocity      = Vector(0,0);
    m_acceleration  = Vector(0,0);
    setDensity(0.01);
}
Controller::Controller(const Controller &controller)
{
    //qDebug() << "Controller(const Controller &controller)";
    this->m_velocity         = controller.m_velocity;
    this->m_acceleration     = controller.m_acceleration;
    this->m_velocityList     = controller.m_accelerationList;
    this->m_accelerationList = controller.m_accelerationList;
}
Controller::~Controller()
{
    //qDebug() << "~Controller()";
}

void Controller::tick(double timeInterval,b2Body *body)
{
    // calculate delta V from acceleration
    Vector deltaV;
    if(m_accelerationList.size() > 0)
    {
        m_acceleration += m_accelerationList;
        m_accelerationList.clear();
        m_accelerationList.reserve(10);
        deltaV = m_acceleration * timeInterval;
        this->addVelocity(deltaV);

    }
    m_acceleration.setLength(0);
    //------------------------------------

    // calculate new Velocity
    Vector sum(0,0);
    sum+=m_velocityList;
    if(sum.getX() != 0 || sum.getY() != 0)
    {

    }
    //qDebug() << sum.getX() << "\t"<<sum.getY();
    b2Vec2 pulse(sum.getX(),sum.getY());
    body->ApplyLinearImpulseToCenter(pulse,false);
    //body->ApplyForceToCenter(pulse,true);
    m_velocity += m_velocityList;
    m_velocityList.clear();
    m_velocityList.reserve(10);
    //------------------------------------

    //qDebug() << "deltaV: "<<deltaV.toString().c_str()
    //         << "     V: "<<m_velocity.toString().c_str();
    //qDebug() <<Vector::radToDeg(m_velocity.getAngle())<<";"<<m_velocity.getLength();
}

void Controller::setVelocity(const Vector &vel)
{
    m_velocity = vel;
}
Vector Controller::getVelocity() const
{
    return m_velocity;
}

void Controller::setAcceleration(const Vector &acc)
{
    m_acceleration = acc;
}
Vector Controller::getAcceleration() const
{
    return m_acceleration;
}

void Controller::addVelocity(const Vector &vel)
{
    m_velocityList.push_back(vel);
}
void Controller::addAcceleration(const Vector &acc)
{
    m_accelerationList.push_back(acc);
}
void Controller::setDensity(double density)
{
    m_density = abs(density);
}
