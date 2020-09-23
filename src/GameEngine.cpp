#include "GameEngine.h"

GameEngine::GameEngine(unsigned int width, unsigned int height,const std::string &windowname)
{
    m_engineRunning = false;
    this->setTickInterval(0.02); // 20ms
    this->setDisplayInterval(0.02); // 20ms
    this->setSimulationsTimeMultiplyer(1);
    m_simulationsTimeInterval = 0;

    this->set_userTimer_1(1); this->set_userTimer_1_enable(false);
    this->set_userTimer_2(2); this->set_userTimer_2_enable(false);
    this->set_userTimer_3(3); this->set_userTimer_3_enable(false);
    this->set_userTimer_4(4); this->set_userTimer_4_enable(false);
    this->set_userTimer_5(5); this->set_userTimer_5_enable(false);

    setBackgroundColor(sf::Color(50,50,50));



    m_renderWindow = new sf::RenderWindow(sf::VideoMode(width,height), windowname);
    m_windowView = m_renderWindow->getView();

    this->setWindowSize(width,height);
    this->setWindowName(windowname);

    m_gravity = new b2Vec2(0.0f,-9.81);
    m_world = new b2World(*m_gravity);
    m_world->SetSubStepping(false);
    //m_world->set
  /*  m_groundBodyDef.position.Set(0.0f, m_windowSize.y-10);
    m_groundBody = m_world->CreateBody(&m_groundBodyDef);
    m_groundBox.SetAsBox(m_windowSize.x/2, 10.0f);
    m_groundBody->CreateFixture(&m_groundBox, 0.0f);*/
    m_velocityIterations = 6;
    m_positionIterations = 3;

}
GameEngine::~GameEngine()
{
    for(size_t i=0; i<m_gameObjectList.size(); i++)
    {
        delete m_gameObjectList[i];
    }
    m_gameObjectList.clear();
}

void GameEngine::start()
{
    qDebug() << "start engine";
    m_engineRunning = true;

    while(m_engineRunning)
    {
        this->user_loop();
        this->handleUserTimer();

        if(m_tickTimer.start(m_tickInterval))
        {
            Timer t;
            t.start(100);

            this->user_tickLoop();
            this->tick();
            m_world->Step(m_simulationsTimeInterval*m_simulationsTimeMultiplyer,m_velocityIterations,m_positionIterations);

            t.update();
            /*if(t.getTime() > m_tickInterval)
                m_simulationsTimeInterval = t.getTime();
            else if(t.getTime() > 1)
                m_simulationsTimeInterval = 1;
            else
                m_simulationsTimeInterval = m_tickInterval;
            if(m_simulationsTimeInterval == 0)*/
                m_simulationsTimeInterval = 1;

          //  qDebug() << "t: "<<t.getTime();
        }
        if(m_displayTimer.start(m_displayInterval))
        {
            this->user_displayLoop();
            this->draw();
        }
    }
}
void GameEngine::stop()
{
    qDebug() << "stop engine";
    m_renderWindow->close();
    m_engineRunning = false;
}
void GameEngine::setWindowSize(unsigned int width,unsigned int height)
{
    m_windowSize.x = width;
    m_windowSize.y = height;
    m_windowView.setSize(width,height);

    m_renderWindow->setView(m_windowView);
    m_renderWindow->setSize(m_windowSize);
}
sf::Vector2u GameEngine::getWindowSize() const
{
    return m_windowSize;
}
void GameEngine::setWindowName(const std::string &name)
{
    m_windowName = name;
    m_renderWindow->setTitle(m_windowName);
}
std::string GameEngine::getWindowName() const
{
    return m_windowName;
}
void GameEngine::setBackgroundColor(sf::Color color)
{
    m_backgroundColor = color;
}

void GameEngine::setTickInterval(double sec)
{
    m_tickInterval = abs(sec);
    if(m_tickInterval == 0)
        m_tickInterval = 0.0001;
}
void GameEngine::setDisplayInterval(double sec)
{
    m_displayInterval = sec;
}
void GameEngine::set_userTimer_1(double sec)
{
    m_userTimer_1_Interval = sec;
}
void GameEngine::set_userTimer_2(double sec)
{
    m_userTimer_2_Interval = sec;
}
void GameEngine::set_userTimer_3(double sec)
{
    m_userTimer_3_Interval = sec;
}
void GameEngine::set_userTimer_4(double sec)
{
    m_userTimer_4_Interval = sec;
}
void GameEngine::set_userTimer_5(double sec)
{
    m_userTimer_5_Interval = sec;
}
void GameEngine::set_userTimer_1_enable(bool enable)
{
    m_userTimer_1_enable = enable;
}
void GameEngine::set_userTimer_2_enable(bool enable)
{
    m_userTimer_2_enable = enable;
}
void GameEngine::set_userTimer_3_enable(bool enable)
{
    m_userTimer_3_enable = enable;
}
void GameEngine::set_userTimer_4_enable(bool enable)
{
    m_userTimer_4_enable = enable;
}
void GameEngine::set_userTimer_5_enable(bool enable)
{
    m_userTimer_5_enable = enable;
}
unsigned long long GameEngine::getCurrentTick() const
{
    return m_currentTick;
}
double GameEngine::getTickUpdateTime() const
{
    return m_tickInterval;
}

void GameEngine::addGameObject(GameObject *obj)
{
    obj->createBody(m_world);
    m_gameObjectList.push_back(obj);
}
void GameEngine::setSimulationsTimeMultiplyer(double factor)
{
    m_simulationsTimeMultiplyer = factor;
}


void GameEngine::tick()
{
    this->handleEvents();
    this->move();
    //this->checkCollision();
}
void GameEngine::move()
{
    for(size_t i=0; i<m_gameObjectList.size(); i++)
    {
        m_gameObjectList[i]->move(m_simulationsTimeInterval*m_simulationsTimeMultiplyer);
    }
}
void GameEngine::checkCollision()
{
    for(size_t i=0; i<m_gameObjectList.size(); i++)
    {
      // std::vector<GameObject*> tmpList = m_gameObjectList;
       // tmpList.erase(tmpList.begin()+i);
        if(!isInFrame(m_gameObjectList[i]))
            continue;

        std::vector<GameObject*> tmpList;
        tmpList.reserve(m_gameObjectList.size());
        for(size_t b=0; b<m_gameObjectList.size(); b++)
        {
            if(!isInFrame(m_gameObjectList[b]) || b == i)
                continue;
            tmpList.push_back(m_gameObjectList[b]);
        }

        m_gameObjectList[i]->checkCollision(tmpList);
    }
}
void GameEngine::draw()
{
    m_renderWindow->clear(m_backgroundColor);
    for(size_t i=0; i<m_gameObjectList.size(); i++)
    {
       // if(!isInFrame(m_gameObjectList[i]))
       //     continue;
        m_gameObjectList[i]->draw(m_renderWindow);
    }
    m_renderWindow->display();
}
void GameEngine::handleEvents()
{
    if(!m_renderWindow->isOpen())
    {
        this->stop();
    }
    sf::Event event;
    while(m_renderWindow->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                this->stop();
                break;
            }
            case sf::Event::Resized:
            {
                this->setWindowSize(m_windowSize.x,m_windowSize.y);
                break;
            }
        }
    }

}

void GameEngine::handleUserTimer()
{
    if(m_userTimer_1_enable)
        if(m_userTimer_1.start(m_userTimer_1_Interval))
            user_loop_timer_1();
    if(m_userTimer_2_enable)
        if(m_userTimer_2.start(m_userTimer_2_Interval))
            user_loop_timer_2();
    if(m_userTimer_3_enable)
        if(m_userTimer_3.start(m_userTimer_3_Interval))
            user_loop_timer_3();
    if(m_userTimer_4_enable)
        if(m_userTimer_4.start(m_userTimer_4_Interval))
            user_loop_timer_4();
    if(m_userTimer_5_enable)
        if(m_userTimer_5.start(m_userTimer_5_Interval))
            user_loop_timer_5();
}

bool GameEngine::isInFrame(GameObject *obj)
{
    Vector pos = obj->getPos();
    Vector size = obj->getSize();
    if(pos.getX()+size.getX() < 0)
        return false;
    if(pos.getX() > m_windowSize.x)
        return false;
    if(pos.getY()+size.getY() < 0)
        return false;
    if(pos.getY() > m_windowSize.y)
        return false;

    return true;
}
