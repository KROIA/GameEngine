#include "gameObject.h"

GameObject::GameObject()
{
    //m_controller.setVelocity(Vector(0,0));
    m_painter.setScale(100,100);
    m_pos = Vector(0,0);
    m_lastVel = Vector(0,0);
}
GameObject::~GameObject()
{
    for(size_t controller = 0; controller<m_controllerList.size(); controller++)
    {
        delete m_controllerList[controller];
    }
    m_controllerList.clear();
}

void GameObject::addCollider(Collider collider)
{
    m_colliderList.push_back(collider);
}
void GameObject::addController(Controller* controller)
{
    m_controllerList.push_back(controller);
}
void GameObject::addPainter(Painter painter)
{
    m_painterList.push_back(painter);
}

void GameObject::tick(double timeInterval)
{
    for(size_t i = 0; i < m_controllerList.size(); i++)
    {
        Controller* controller = m_controllerList[i];
        controller->tick(timeInterval);
        m_lastVel += controller->getVelocity();
    }
   // m_controller.tick(timeInterval);
    m_pos += m_lastVel * timeInterval;
}
void GameObject::draw(sf::RenderWindow *window)
{
    m_painter.draw(window,m_pos);
}
