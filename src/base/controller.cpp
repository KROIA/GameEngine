#include "controller.h"


vector<Controller*>  Controller::controller_list;

Controller::Controller()
{
    m_ID = Controller::controller_list.size();
    Controller::controller_list.push_back(this);

    m_p_func_onMove = nullptr;
    m_p_obj = nullptr;
    this->setMass(1);
    this->setSize(coordinateU{1,1});
    this->setVelocity(Velocity{.velocity=0,.direction=coordinateF{0,0}});
    this->gravity(false);
    this->setPosition(coordinate{1,1});

}

Controller::~Controller()
{
    //EngineBase::__deleteLater(TYPE_TAG_CONTROLLER,m_ID);
    //Controller::controller_list.erase(Controller::controller_list.begin()+m_ID);
}

void Controller::update()
{
    coordinate deltaPos;
    deltaPos.x = m_velocity.direction.x*m_velocity.velocity;
    deltaPos.y = m_velocity.direction.y*m_velocity.velocity;

    if(deltaPos.x != 0 || deltaPos.y != 0)
        this->move(deltaPos);


    applyMoveList();
}


void Controller::gravity(bool enable)
{
    m_enable_gravity = enable;
}
bool Controller::gravity()
{
    return m_enable_gravity;
}

void Controller::setVelocity(Velocity vel)
{
    m_velocity = vel;
}
Velocity Controller::getVelocity()
{
    return m_velocity;
}
void Controller::setMass(double mass)
{
    if(mass <= 0)
        mass = 0.001;
    m_mass = mass;
}
double Controller::getMass()
{
    return m_mass;
}
void Controller::move(coordinate deltaPos)
{
    m_moveList.push_back(deltaPos);
}

void Controller::setPosition(coordinate pos)
{
    EngineBase::checkOutOfBoarder(pos);
    m_pos = pos;
}
coordinate Controller::getPosition()
{
    return m_pos;
}
void Controller::setSize(coordinateU size)
{
    m_size = size;
}
coordinateU Controller::getSize()
{
    return m_size;
}
void Controller::setEvent_onMove(GameObject *obj, void (GameObject::*p_func)(Controller*,coordinate))
{
    m_p_obj = obj;
    m_p_func_onMove = p_func; // Setze Funktion die beim Event ausgeführt erden soll
}
void Controller::sendEvent_onMove(coordinate deltaPos)
{
    if(m_p_func_onMove != nullptr) // Nur ausführen, wenn die Funktion gesetzt wurde
    {
     //   qDebug() << "controller ID: "<<this->m_ID;
        (m_p_obj->*m_p_func_onMove)(this,deltaPos); // Führe die Funktion aus
    }
}

void Controller::applyMoveList()
{
   // m_lastPos = m_pos;
    for(unsigned int a=0; a<m_moveList.size(); a++)
    {
       // m_pos.x+=m_moveList[a].x;
       // m_pos.y+=m_moveList[a].y;

        if((signed)m_pos.x<-m_moveList[a].x)
        {
           // m_lastPos.x = m_pos.x;
            m_pos.x = 0;
            m_velocity.direction.x=0;
        }
        else if(m_pos.x+m_size.x+m_moveList[a].x <= EngineBase::mapSize.x)
        {
          //  m_lastPos.x = m_pos.x;
            m_pos.x+=m_moveList[a].x;
        }else
        {
            m_pos.x = EngineBase::mapSize.x-m_size.x;
            m_velocity.direction.x=0;
        }


        if((signed)m_pos.y<-m_moveList[a].y)
        {
           // m_lastPos.y = m_pos.y;
            m_pos.y = 0;
            m_velocity.direction.y=0;
        }
        else if(m_pos.y+m_size.y+m_moveList[a].y <= EngineBase::mapSize.y)
        {
           // m_lastPos.y = m_pos.y;
            m_pos.y+=m_moveList[a].y;
        }else
        {
            m_pos.y = EngineBase::mapSize.y-m_size.y;
            m_velocity.direction.y=0;
        }
    }
    m_moveList.clear();
    m_moveList.reserve(10);
}

