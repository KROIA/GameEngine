#include "gameObject.h"

vector<GameObject*> GameObject::gameObject_list;

GameObject::GameObject()
{
    m_ID = GameObject::gameObject_list.size();
    GameObject::gameObject_list.push_back(this);

    // Verbinde das event mit einer Funktion aus diesem Objekt
    m_collider.setEvent_onCollision(this,&GameObject::event_onCollision);

    skipUpdateSettings = true;
    m_painter.setColor(sf::Color(255,0,0));
    m_controller.setSize(coordinateU(1,1));
    m_controller.setPosition(coordinate(0,0));
    m_lastPos = m_controller.getPosition();


    skipUpdateSettings = false;



   // m_controller.setEvent_onMove(this,&GameObject::event_onMove);
    this->updateSettings();
}

GameObject::~GameObject()
{
    //EngineMisc::__deleteLater(TYPE_TAG_GAMEOBJECT,m_ID);
}
void GameObject::update()
{
    m_lastPos = m_controller.getPosition();


    m_controller.update();

    m_collider.setPosition(m_controller.getPosition());
    m_collider.setSize(m_controller.getSize());

    m_painter.setPosition(m_controller.getPosition());
    m_painter.setSize(m_controller.getSize());
}



void GameObject::updateSettings()
{

}

Controller *GameObject::getController()
{
    return &m_controller;
}

void GameObject::event_onCollision(Collider *collider) // Eventreciever
{
    m_controller.setPosition(m_lastPos);
    m_controller.setVelocity(Velocity{.velocity=0,.direction=coordinateF{0,0}});

    this->update();
}

