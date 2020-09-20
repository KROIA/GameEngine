#include "gravityController.h"

GravityController::GravityController()
    : Controller()
{
    m_gravityDeltaV.setLength(9.81);
    m_gravityDeltaV.setAngle(M_PI*0.5); // 90 deg
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

void GravityController::tick(double timeInterval)
{
    this->setVelocity(Vector(0,0));
    this->addAcceleration(m_gravityDeltaV);
    Controller::tick(timeInterval);
}
