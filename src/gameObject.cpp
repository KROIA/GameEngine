#include "gameObject.h"

GameObject::GameObject()
{
    m_pos           = Vector(0,0);
    m_lastPos       = m_pos;
    m_velocity      = Vector(0,0);
    m_lastVelocity  = m_velocity;

    this->setStatic(false);
    this->setSize(50,50);
}
GameObject::~GameObject()
{
    for(size_t i = 0; i<m_colliderList.size(); i++)
    {
        delete m_colliderList[i];
    }
    for(size_t i = 0; i<m_controllerList.size(); i++)
    {
        delete m_controllerList[i];
    }
    for(size_t i = 0; i<m_painterList.size(); i++)
    {
        delete m_painterList[i];
    }
    m_colliderList.clear();
    m_controllerList.clear();
    m_painterList.clear();
}

void GameObject::addCollider(Collider *collider)
{
    collider->setSize(m_size);
    m_colliderList.push_back(collider);
}
void GameObject::addController(Controller* controller)
{
    m_controllerList.push_back(controller);
}
void GameObject::addPainter(Painter *painter)
{
    painter->setSize(m_size);
    m_painterList.push_back(painter);
}

void GameObject::move(double timeInterval)
{
    //m_lastPos       = m_pos;
    Vector vel(0,0);
    for(size_t i = 0; i < m_controllerList.size(); i++)
    {
        Controller* controller = m_controllerList[i];
        controller->tick(timeInterval);
        vel += controller->getVelocity();
    }
    this->setVelocity(this->m_lastVelocity+vel);
    this->movePos(m_velocity * timeInterval);
    //m_pos += m_velocity * timeInterval;

    // Move all colliders

   // qDebug() <<"pos: " <<m_pos.toString().c_str();
}
bool GameObject::checkCollision(GameObject *other)
{
    Collider *thisCollider;
    Collider *otherCollider;
    for(size_t a=0; a<m_colliderList.size(); a++)
    {
        thisCollider = m_colliderList[a];
        for(size_t i=0; i<other->m_colliderList.size(); i++)
        {
            otherCollider = other->m_colliderList[i];

            if(thisCollider == otherCollider)
                continue;

            //Vector collisionVec(0,0);
            //if(thisCollider->collides(otherCollider,collisionVec))
            if(thisCollider->collides(otherCollider,this->m_velocity,other->m_velocity))
            {
                /*Vector thisCenter = thisCollider->getCenter();
                Vector otherCenter = otherCollider->getCenter();
                Vector driftOutVec =  thisCenter - otherCenter;

                this->setVelocity(Vector(0,0));
                this->movePos(driftOutVec*0.1);*/
                //m_pos += driftOutVec;
                //qDebug() << "drift: "<<driftOutVec.toString().c_str();

                //qDebug() << " collision!";
                //m_pos   = m_lastPos;

                if(!this->m_isStatic)
                {
                    Vector lastPos = m_lastPos;
                    this->setVelocity(Vector(0,0));
                    this->setPos(m_lastPos);
                    m_lastPos = lastPos;
                    m_lastVelocity = m_velocity;
                }

                //m_pos += collisionVec;
             //   Vector rotatedCollisionVecor = collisionVec;
             //   rotatedCollisionVecor.rotate(-M_PI/2);

                return true; // collision
            }
        }
    }
    return false;
}
bool GameObject::checkCollision(std::vector<GameObject*> others)
{

    for(size_t i=0; i<others.size(); i++)
    {
        if(this->checkCollision(others[i]))
        {
            //m_pos   = m_lastPos;
            return true; // collision
        }
    }
    return false;
}
void GameObject::draw(sf::RenderWindow *window)
{
    for(size_t i=0; i<m_painterList.size(); i++)
        m_painterList[i]->draw(window,m_pos);
}

void GameObject::movePos(Vector delta)
{
    if(!m_isStatic)
        this->setPos(m_pos + delta);
}
void GameObject::setPos(Vector pos)
{
    m_lastPos   = m_pos;
    m_pos       = pos;

    for(size_t i=0; i<m_colliderList.size(); i++)
    {
        m_colliderList[i]->setPos(m_pos);

    }
}
void GameObject::setPos(double x, double y)
{
    m_lastPos = m_pos;
    m_pos.setX(x);
    m_pos.setY(y);
    for(size_t i=0; i<m_colliderList.size(); i++)
    {
        m_colliderList[i]->setPos(m_pos);
    }
}
Vector GameObject::getPos() const
{
    return m_pos;
}
void GameObject::setSize(Vector size)
{
    m_size = size;
    for(size_t i=0; i<m_colliderList.size(); i++)
    {
        m_colliderList[i]->setSize(m_size);
    }
    for(size_t i=0; i<m_painterList.size(); i++)
    {
        m_painterList[i]->setSize(m_size);
    }
}
void GameObject::setSize(double x, double y)
{
    m_size.setX(x);
    m_size.setY(y);
    for(size_t i=0; i<m_colliderList.size(); i++)
    {
        m_colliderList[i]->setSize(m_size);
    }
    for(size_t i=0; i<m_painterList.size(); i++)
    {
        m_painterList[i]->setSize(m_size);
    }
}
Vector GameObject::getSize() const
{
    return m_size;
}
void GameObject::setVelocity(Vector vel)
{
    m_lastVelocity  = m_velocity;
    m_velocity      = vel;
}
void GameObject::setStatic(bool enable)
{
    m_isStatic = enable;
}
