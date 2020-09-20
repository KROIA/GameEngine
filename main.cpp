#include "mainwindow.h"
#include <QApplication>
//#include "GameEngine.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>

#include "cubeCollider.h"
#include "gravityController.h"
#include "keyController.h"
#include "painter.h"
#include "gameObject.h"
#include "timer.h"
#include <SFML/Graphics.hpp>


#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    sf::RenderWindow *m_renderWindow = new sf::RenderWindow(sf::VideoMode(800,800), "m_windowName");

    KeyController* keyCtrl = new KeyController(sf::Keyboard::A,
                                              sf::Keyboard::D,
                                              sf::Keyboard::W,
                                              sf::Keyboard::S);
   /* KeyController keyCtrl(sf::Keyboard::A,
                                                  sf::Keyboard::D,
                                                  sf::Keyboard::W,
                                                  sf::Keyboard::S);*/

    GravityController * gravity= new GravityController();
    GameObject object;
    object.addController(keyCtrl);
    object.addController(gravity);


    Timer timer;

    double frameTime = 0.02;
    double simulationsTime = 0.05;
    bool run = true;
    while(run)
    {
        if(timer.start(frameTime))
        {
            //std::cout<< "tick";

            if(!m_renderWindow->isOpen())
            {
                run = false;
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
                        run = false;
                        break;
                    }
                }
            }

            object.tick(simulationsTime);

            m_renderWindow->clear(sf::Color(50,50,50));

            object.draw(m_renderWindow);
            m_renderWindow->display();
        }
    }

    //GameEngine engine;



    /*while(engine.isRunning())
    {
        engine.update();
    }*/
    //a.exec();
    w.close();
    a.exit();
    return 0;
}
