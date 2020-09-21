#include "mainwindow.h"
#include <QApplication>
//#include "GameEngine.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>

#include "rectCollider.h"
#include "gravityController.h"
#include "keyController.h"
#include "painter.h"
#include "gameObject.h"
#include "timer.h"
#include <SFML/Graphics.hpp>
#include "vectorFunction.h"
#include "GameEngine.h"

#include <QDebug>

void generateObsticles(GameEngine *engine, unsigned int amount);
void generateGround(GameEngine *engine, unsigned int tiles);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
/*
    VectorFunction function1;
    Vector base1;
    base1.setX(-1);base1.setY(-5);
    function1.setBase(base1);
    Vector dir1;
    dir1.setX(-1);dir1.setY(0.2);
    function1.setDirection(dir1);

    VectorFunction function2;
    Vector base2;
    base2.setX(1);base2.setY(5);
    function2.setBase(base2);
    Vector dir2;
    dir2.setX(1);dir2.setY(1);
    function2.setDirection(dir2);

    for(int a= -10; a<10; a++)
    {
        qDebug() << a << "\t" << function1.getPoint(a).getX()<<"\t"<<function1.getPoint(a).getY()<<"\t\t" << function2.getPoint(a).getX()<<"\t"<<function2.getPoint(a).getY();
    }
    qDebug() << "intersection1:\t"<<function1.getIntersection(function2).getX()<<"\t" <<function1.getIntersection(function2).getY();
    qDebug() << "intersection2:\t"<<function2.getIntersection(function1).getX()<<"\t" <<function2.getIntersection(function1).getY();


    qDebug() << "f1: \t0\t0";
    qDebug() << "    \t"<<base1.getX()<<"\t"<<base1.getY();
    qDebug() << "    \t"<<(base1+dir1).getX()<<"\t"<<(base1+dir1).getY();
    qDebug() << "";
    qDebug() << "f2: \t0\t0";
    qDebug() << "    \t"<<base2.getX()<<"\t"<<base2.getY();
    qDebug() << "    \t"<<(base2+dir2).getX()<<"\t"<<(base2+dir2).getY();




    qDebug() << "intersectionFactor1: \t"<<function1.getIntersectionFactor(function2);
    qDebug() << "intersectionFactor2: \t"<<function2.getIntersectionFactor(function1);
    qDebug() << "angle: \t"<<Vector::radToDeg(Vector::getAngle(dir1,dir2));*/

    sf::Vector2u windowSize(1200,700);

    GameEngine engine(windowSize.x,windowSize.y,"myEngine");
    //engine.setWindowSize(windowSize.x,windowSize.y);

    GameObject *myPlayer = new GameObject();
    KeyController *playerKeyController = new KeyController(sf::Keyboard::A,
                                                           sf::Keyboard::D,
                                                           sf::Keyboard::W,
                                                           sf::Keyboard::S);
    GravityController *playerGravityController = new GravityController(9.81);
    RectCollider *playerCollider = new RectCollider();
    Painter *playerPainter = new Painter();
    playerPainter->loadFromFile("E:\\Dokumente\\QT\\Projects\\GameEngine\\textures\\Player.png");


    myPlayer->addController(playerKeyController);
    myPlayer->addController(playerGravityController);
    myPlayer->addCollider(playerCollider);
    myPlayer->setPos(50,100);
    myPlayer->addPainter(playerPainter);
    myPlayer->setSize(50,50);



    generateGround(&engine,50);
    generateObsticles(&engine,100);

    engine.addGameObject(myPlayer);

    engine.setTickInterval(0.05);
    engine.setSimulationsTimeMultiplyer(2);

    engine.start();


   /* sf::RenderWindow *m_renderWindow = new sf::RenderWindow(sf::VideoMode(800,800), "m_windowName");

    KeyController* keyCtrl = new KeyController(sf::Keyboard::A,
                                              sf::Keyboard::D,
                                              sf::Keyboard::W,
                                              sf::Keyboard::S);

    GameObject obsticle;
    RectCollider *obsticleCollider = new RectCollider();
    Painter *obsticlePainter = new Painter();
    obsticlePainter->setColor(sf::Color(100,100,0));
    obsticle.addPainter(obsticlePainter);
    obsticle.addCollider(obsticleCollider);
    obsticle.setPos(400,400);


    GameObject player;
    GravityController * gravity= new GravityController();
    RectCollider *collider = new RectCollider();
    Painter *playerPainter = new Painter();

    playerPainter->loadFromFile("E:\\Dokumente\\QT\\Projects\\GameEngine\\textures\\Player.png");


    player.addPainter(playerPainter);
    player.addController(keyCtrl);
    player.addController(gravity);
    player.addCollider(collider);
    player.setPos(100,100);


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

            player.makeMove(simulationsTime);
            obsticle.makeMove(simulationsTime);

            player.checkCollision(&obsticle);

            m_renderWindow->clear(sf::Color(50,50,50));
            obsticle.draw(m_renderWindow);
            player.draw(m_renderWindow);

            m_renderWindow->display();
        }
    }*/

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
void GameEngine::user_loop()
{
    //qDebug() << " userloop";
}
void GameEngine::user_tickLoop()
{
    //qDebug() << " userTickLoop";
}
void GameEngine::user_loop_timer_1()
{
   qDebug() << " user_loop_timer_1";
}
void GameEngine::user_loop_timer_2()
{
    qDebug() << " user_loop_timer_2";
}
void GameEngine::user_loop_timer_3()
{
    qDebug() << " user_loop_timer_3";
}
void GameEngine::user_loop_timer_4()
{
    qDebug() << " user_loop_timer_4";
}
void GameEngine::user_loop_timer_5()
{
    qDebug() << " user_loop_timer_5";
}


void generateObsticles(GameEngine *engine, unsigned int amount)
{
    Vector tileSize;
    sf::Vector2u windowSize = engine->getWindowSize();
    tileSize.setX(30);
    tileSize.setY(tileSize.getX());
    for(unsigned int i=0; i<amount; i++)
    {
        RectCollider *collider = new RectCollider();
        Painter *painter = new Painter;
        painter->loadFromFile("E:\\Dokumente\\QT\\Projects\\GameEngine\\textures\\Obsticle.png");
        GravityController *controller = new GravityController(9.81);

        GameObject *obj = new GameObject();
        obj->addController(controller);
        obj->addCollider(collider);
        obj->addPainter(painter);
        obj->setPos(i*tileSize.getX(),windowSize.y-tileSize.getY());
        obj->setSize(tileSize);
        obj->setPos(rand()%windowSize.x,-(rand()%amount*10) + windowSize.y/2);
        obj->setVelocity(Vector((rand()%3141)/(double)1000,(rand()%1000)/(double)10));


        engine->addGameObject(obj);
    }
}
void generateGround(GameEngine *engine, unsigned int tiles)
{
    Vector tileSize;
    sf::Vector2u windowSize = engine->getWindowSize();
    tileSize.setX(windowSize.x/(double)tiles);
    tileSize.setY(tileSize.getX());
    for(unsigned int i=0; i<tiles; i++)
    {
        RectCollider *collider = new RectCollider();
        Painter *painter = new Painter;
        painter->loadFromFile("E:\\Dokumente\\QT\\Projects\\GameEngine\\textures\\Ground.png");

        GameObject *obj = new GameObject();
        obj->addCollider(collider);
        obj->addPainter(painter);
        obj->setPos(i*tileSize.getX(),windowSize.y-tileSize.getY());
        obj->setSize(tileSize);


        engine->addGameObject(obj);
    }
}
