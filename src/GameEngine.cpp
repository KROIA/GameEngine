#include "GameEngine.h"


GameEngine::GameEngine()
{
    m_settingsSkipUpdate = true;
    m_isRunning = true;

    this->setWindowSize(coordinateU(500,500));
    this->setWindowName("GameEngine window name");

    m_renderWindow = new sf::RenderWindow(sf::VideoMode(m_windowSize.x,m_windowSize.y), m_windowName);

    this->setMapSize(coordinate(100,100));



    this->setBackgroundColor(sf::Color(0,150,150));


    m_settingsSkipUpdate = false;
    m_object.getController()->gravity(true);
    m_object.getController()->setPosition(coordinate(8,8));
    m_object.getController()->setSize(coordinateU(10,10));

    m_object_2.getController()->gravity(true);
    m_object_2.getController()->setPosition(coordinate(40,90));
    m_object_2.getController()->setSize(coordinateU(20,5));

/*Collider test;
    Collider test2;
    test = test2;*/

    m_boarder.push_back(new Collider());
    m_boarder.push_back(new Collider());
    m_boarder.push_back(new Collider());
    m_boarder.push_back(new Collider());



    unsigned int boarderThickness = 1000;
    m_boarder[0]->setSize(coordinateU(m_mapSize.x + 2*boarderThickness,boarderThickness)); // top
    m_boarder[1]->setSize(coordinateU(boarderThickness,m_mapSize.y)); // right
    m_boarder[2]->setSize(coordinateU(m_mapSize.x + 2*boarderThickness,boarderThickness)); // bottom
    m_boarder[3]->setSize(coordinateU(boarderThickness,m_mapSize.y)); // left

    m_boarder[0]->setPosition(coordinate(-boarderThickness,-boarderThickness));
    m_boarder[1]->setPosition(coordinate(m_mapSize.x,0));
    m_boarder[2]->setPosition(coordinate(-boarderThickness,m_mapSize.y));
    m_boarder[3]->setPosition(coordinate(-boarderThickness,0));

    m_ground.getController()->setSize(coordinateU(m_mapSize.x + 2*boarderThickness,boarderThickness));
    m_ground.getController()->setPosition(coordinate(50,50));

    this->updateSettings();
    m_timer1_start  = std::chrono::high_resolution_clock::now();
    m_timer1_end  = std::chrono::high_resolution_clock::now();

    m_frameUpdateTimer.setAutorestart(true);
    m_physicsUpdateTimer.setAutorestart(true);
}

GameEngine::~GameEngine()
{
    this->close();
    delete m_renderWindow;
}

void GameEngine::setWindowSize(coordinateU windowSize)
{
    m_windowSize = windowSize;
    this->updateSettings();
}
void GameEngine::setWindowName(string name)
{
    m_windowName = name;
    this->updateSettings();
}
bool GameEngine::isRunning()
{
    return m_isRunning;
}
void GameEngine::close()
{
    m_renderWindow->close();
}
void GameEngine::update()
{
    // Only update on a specific timeinterval

    if(m_physicsUpdateTimer.start(1.0/EngineMisc::physicsTicksPerSecond))
    {
        this->handleEvent();


        this->calculatePhysics();
        this->checkCollision();

        /*m_timer1_end  = std::chrono::high_resolution_clock::now();
        m_time1_span   = std::chrono::duration_cast<std::chrono::microseconds>(m_timer1_end - m_timer1_start);

        if(m_time1_span.count() > 0.000000001 && EngineMisc::sycle) //sycle > 0
        {
            EngineMisc::updateDurationTime = m_time1_span.count();
            EngineMisc::framesPerSecond = EngineMisc::framesPerSecond*0.99+0.01/EngineMisc::updateDurationTime;
        }
        m_timer1_start  = std::chrono::high_resolution_clock::now();


        EngineMisc::sycle++;
        EngineMisc::tmpSycleCounter++;*/
       if(EngineMisc::tmpSycleCounter > 100)
        {
            EngineMisc::tmpSycleCounter = 0;
            qDebug() << "FPS: "<<EngineMisc::framesPerSecond << "\t sycle: "<<EngineMisc::sycle;
      //      this->__deleteTargets();
        }
    }

    if(m_frameUpdateTimer.start(1.0/EngineMisc::framesPerSecondTarget))
    {

        this->updateGraphics();
    }
}

void GameEngine::setMapSize(coordinate mapsize)
{
    m_mapSize = mapsize;
    if(m_mapSize.x < 1 || m_mapSize.y < 1)
    {
        // invalid mapsize
        m_mapSize.x = 1;
        m_mapSize.y = 1;
    }
    EngineMisc::mapSize = m_mapSize;
    this->updateSettings();
}

void GameEngine::setBackgroundColor(sf::Color color)
{
    m_backgroundColor = color;
    this->updateSettings();
}


// private

void GameEngine::checkCollision()
{
    for(unsigned int a=0; a<Collider::collider_list.size(); a++)
    {
        for(unsigned int b=a+1; b<Collider::collider_list.size(); b++)
        {
            if(Physics::isCollided(Collider::collider_list[a],Collider::collider_list[b]))
            {
                Collider::collider_list[a]->sendEvent_onCollision();
                Collider::collider_list[b]->sendEvent_onCollision();
                qDebug() << "Collision "<<a << " "<<b;
            }
        }
    }
}
void GameEngine::calculatePhysics()
{
    for(unsigned int a=0; a<Controller::controller_list.size(); a++)
    {
        if(Controller::controller_list[a]->gravity())//Gravity enabled?
            Physics::applyGravity(Controller::controller_list[a]);
    }
    for(unsigned int a=0; a<GameObject::gameObject_list.size(); a++)
    {
        GameObject::gameObject_list[a]->update();
    }
}

void GameEngine::updateSettings()
{
    if(m_settingsSkipUpdate)
        return;

    if(m_renderWindow != nullptr)
    {
        m_renderWindow->setSize(m_windowSize);
        m_renderWindow->setTitle(m_windowName);
    }

    m_backgroundImage.create(m_mapSize.x,m_mapSize.y,m_backgroundColor);
    m_backgroundTexture.loadFromImage(m_backgroundImage);
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setPosition(0,0);
    m_backgroundSprite.setScale(m_windowSize.x/m_mapSize.x,m_windowSize.y/m_mapSize.y);

    m_graphicsScale.x = m_windowSize.x/m_mapSize.x;
    m_graphicsScale.y = m_windowSize.y/m_mapSize.y;

    EngineMisc::mapSize = m_mapSize;
    EngineMisc::graphicScale = m_graphicsScale;

    m_object.updateSettings();
    m_object_2.updateSettings();
}

// Events
void GameEngine::handleEvent()
{

    if(!m_renderWindow->isOpen())
    {
        return;
    }
    sf::Event event;
    while(m_renderWindow->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                qDebug() << "close";
                m_renderWindow->close();
                m_isRunning = false;
                break;
            }
        case sf::Event::KeyPressed:
            {
                //this->handleKeyEvent(event);
                break;
            }
        }
    }
    this->handleKeyEvent(event);


}
void GameEngine::handleKeyEvent(sf::Event &event)
{
    Velocity vel1 = m_object.getController()->getVelocity();
    double velocity = 1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){m_object.getController()->setVelocity(Physics::velocity_add(m_object.getController()->getVelocity(),Velocity{.velocity=velocity,.direction=coordinateF{0,-8}}));  }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){m_object.getController()->setVelocity(Physics::velocity_add(m_object.getController()->getVelocity(),Velocity{.velocity=velocity,.direction=coordinateF{0,-5}}));  }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){m_object.getController()->setVelocity(Physics::velocity_add(m_object.getController()->getVelocity(),Velocity{.velocity=velocity,.direction=coordinateF{-1,0}}));  }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){m_object.getController()->setVelocity(Physics::velocity_add(m_object.getController()->getVelocity(),Velocity{.velocity=velocity,.direction=coordinateF{0,1}}));  }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){m_object.getController()->setVelocity(Physics::velocity_add(m_object.getController()->getVelocity(),Velocity{.velocity=velocity,.direction=coordinateF{1,0}}));  }

  /*
    switch(event.key.code)
    {
        case sf::Keyboard::Space:
        {
           // qDebug() << "W pressed";
        m_object.getController()->setVelocity(Physics::velocity_add(vel1,Velocity{.velocity=velocity,.direction=coordinateF{0,-8}}));
            //m_object.getController()->setVelocity(Velocity{.velocity = velocity,.direction=coordinateF{0,-15}});
            //m_object.move(sf::Vector2<int>(0,-1));
            break;
        }
        case sf::Keyboard::W:
        {
           // qDebug() << "W pressed";
            m_object.getController()->setVelocity(Physics::velocity_add(vel1,Velocity{.velocity=velocity,.direction=coordinateF{0,-5}}));
            //m_object.getController()->setVelocity(Velocity{.velocity = velocity,.direction=coordinateF{0,-15}});
            //m_object.move(sf::Vector2<int>(0,-1));
            break;
        }
        case sf::Keyboard::A:
        {
            m_object.getController()->setVelocity(Physics::velocity_add(vel1,Velocity{.velocity=velocity,.direction=coordinateF{-1,0}}));
            //m_object.getController()->setVelocity(Velocity{.velocity = velocity,.direction=coordinateF{-1,0}});
            //m_object.move(sf::Vector2<int>(-1,0));
            break;
        }
        case sf::Keyboard::S:
        {
            m_object.getController()->setVelocity(Physics::velocity_add(vel1,Velocity{.velocity=velocity,.direction=coordinateF{0,1}}));
            //m_object.getController()->setVelocity(Velocity{.velocity = velocity,.direction=coordinateF{0,1}});
            //m_object.move(sf::Vector2<int>(0,1));
            break;
        }
        case sf::Keyboard::D:
        {
            m_object.getController()->setVelocity(Physics::velocity_add(vel1,Velocity{.velocity=velocity,.direction=coordinateF{1,0}}));
            //m_object.getController()->setVelocity(Velocity{.velocity = velocity,.direction=coordinateF{1,0}});
            //m_object.move(sf::Vector2<int>(1,0));
            break;
        }
    }*/
}


void GameEngine::updateGraphics()
{
    m_renderWindow->draw(m_backgroundSprite);

    for(unsigned int a=0; a<Painter::painter_list.size(); a++)
    {
        m_renderWindow->draw(*Painter::painter_list[a]->getSprite());
    }

    // end the current frame
    m_renderWindow->display();
}

void GameEngine::__deleteTargets()
{
    if(EngineMisc::__deleteTargetList.size() == 0)
        return;
    qDebug() << "Deleting "<<EngineMisc::__deleteTargetList.size()<<" targets...";
    for(size_t target=0; target<EngineMisc::__deleteTargetList.size(); target++)
    {
        switch(EngineMisc::__deleteTargetList[target].typeTag)
        {
            case TYPE_TAG_COLLIDER:
            {
                Collider::collider_list.erase(Collider::collider_list.begin()+EngineMisc::__deleteTargetList[target].ID);
                break;
            }
            case TYPE_TAG_GAMEOBJECT:
            {
                GameObject::gameObject_list.erase(GameObject::gameObject_list.begin()+EngineMisc::__deleteTargetList[target].ID);
                break;
            }
            case TYPE_TAG_CONTROLLER:
            {
                Controller::controller_list.erase(Controller::controller_list.begin()+EngineMisc::__deleteTargetList[target].ID);
                break;
            }
        }
    }
    EngineMisc::__deleteTargetList.clear();
}
