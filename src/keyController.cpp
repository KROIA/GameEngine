#include "keyController.h"

KeyController::KeyController
             (sf::Keyboard::Key keyLeft,
              sf::Keyboard::Key keyRight,
              sf::Keyboard::Key keyUp,
              sf::Keyboard::Key keyDown)
    : Controller()
{
    m_keyLeft   = keyLeft;
    m_keyRight  = keyRight;
    m_keyUp     = keyUp;
    m_keyDown   = keyDown;

    m_leftMove  = Vector(Vector::degToRad(180),15);
    m_rightMove = Vector(Vector::degToRad(0)  ,15);
    m_upMove    = Vector(Vector::degToRad(270),15);
    m_downMove  = Vector(Vector::degToRad(90) ,15);
}
KeyController::KeyController(const KeyController &controller)
    : Controller(controller)
{
    this->m_keyLeft   = controller.m_keyLeft;
    this->m_keyRight  = controller.m_keyRight;
    this->m_keyUp     = controller.m_keyUp;
    this->m_keyDown   = controller.m_keyDown;

    this->m_leftMove  = controller.m_leftMove;
    this->m_rightMove = controller.m_rightMove;
    this->m_upMove    = controller.m_upMove;
    this->m_downMove  = controller.m_downMove;
}
KeyController::~KeyController()
{
    //qDebug()<<"~KeyController()";
}

void KeyController::tick(double timeInterval)
{
    this->m_velocity *= 0.1;
    this->handleKeyPress(timeInterval);
    Controller::tick(timeInterval);
}

void KeyController::handleKeyPress(double timeInterval)
{
    if(sf::Keyboard::isKeyPressed(m_keyLeft))
    {
        this->addVelocity(m_leftMove*timeInterval);
    }
    if(sf::Keyboard::isKeyPressed(m_keyRight))
    {
        this->addVelocity(m_rightMove*timeInterval);
    }
    if(sf::Keyboard::isKeyPressed(m_keyUp))
    {
        this->addVelocity(m_upMove*timeInterval);
    }
    if(sf::Keyboard::isKeyPressed(m_keyDown))
    {
        this->addVelocity(m_downMove*timeInterval);
    }
}
