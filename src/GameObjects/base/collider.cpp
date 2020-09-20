#include "collider.h"

vector<Collider*>  Collider::collider_list;

Collider::Collider()
{
    m_ID = Collider::collider_list.size();
    Collider::collider_list.push_back(this);
    this->setSize(coordinateU(1,1));
    this->setPosition(coordinate(0,0));

    m_p_func_onCollision = nullptr;
    m_p_obj = nullptr;




}
Collider::Collider(const Collider &original)
{
    m_ID = Collider::collider_list.size();
    Collider::collider_list.push_back(this);
    qDebug() << "copy";
}
Collider::~Collider()
{
    //
    //EngineMisc::__deleteLater(TYPE_TAG_COLLIDER,m_ID);
    Collider::collider_list.erase(Collider::collider_list.begin()+m_ID);
}


void Collider::setPosition(coordinate pos)
{
    EngineMisc::checkOutOfBoarder(pos);
    m_pos = pos;
}
void Collider::setSize(coordinateU size)
{
    //EngineMisc::checkOutOfBoarder(size);
    m_size = size;
}


coordinate Collider::getPos()
{
    return m_pos;
}
coordinateU Collider::getSize()
{
    return m_size;
}


void Collider::setEvent_onCollision(GameObject *obj, void (GameObject::*p_func)(Collider*))
{
    m_p_obj = obj;  // Setzt das Target Object
    m_p_func_onCollision = p_func; // Setze Funktion die beim Event ausgeführt erden soll
}
void Collider::sendEvent_onCollision()
{
    if(m_p_func_onCollision != nullptr) // Nur ausführen, wenn die Funktion gesetzt wurde
    {
        (m_p_obj->*m_p_func_onCollision)(this); // Führe die Funktion aus
    }
}
