#include "gravityController.h"

GravityController::GravityController()
    : Controller()
{
    // 90 deg
    this->setForceVector(Vector(M_PI*0.5,9.81));
}
GravityController::GravityController(double force)
{
    this->setForceVector(Vector(M_PI*0.5,force));
}
GravityController::GravityController(const GravityController &controller)
    : Controller(controller)
{
    //qDebug() << "GravityController(const GravityController &controller)";
    this->m_gravityDeltaV = controller.m_gravityDeltaV;

}
GravityController::~GravityController()
{

}
void GravityController::setForce(double force)
{
    m_gravityDeltaV.setLength(abs(force));
}
void GravityController::setForceVector(Vector force)
{
    m_gravityDeltaV = force;
}

void GravityController::tick(double timeInterval)
{
    this->setVelocity(Vector(0,0));
    this->addAcceleration(m_gravityDeltaV);
    Controller::tick(timeInterval);
}
