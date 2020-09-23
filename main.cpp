#include "mainwindow.h"
#include <QApplication>
//#include "GameEngine.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>

#include "rectCollider.h"
#include "circleCollider.h"
#include "gravityController.h"
#include "keyController.h"
#include "painter.h"
#include "gameObject.h"
#include "timer.h"
#include <SFML/Graphics.hpp>
#include "vectorFunction.h"
#include "GameEngine.h"

#include <QDebug>

const std::string texturePath = "..\\..\\textures\\";
std::vector<GameObject*> particleList;

void generateObsticles(GameEngine *engine, unsigned int amountX,unsigned int amountY);
void generateGround(GameEngine *engine, unsigned int tiles);
void generateWall(GameEngine *engine, unsigned int tiles,double posX,double posY,int size);
void vectorTest();

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

    //vectorTest();
    //return 0;

    /*Vector vec(0,1);
    Vector vec2(0,1);
    qDebug() << "angle\tlength\tx\ty";
   // qDebug() << "v1x\tv1y\tv2x\tv2y";
    for(int a=0; a<360*3; a++)
    {
        vec.rotate(Vector::degToRad(1));
        vec*=0.999;
        vec2 += vec;
        qDebug() << vec2.getAngle() << "\t"<<vec2.getLength()<<"\t"<<vec2.getX()<<"\t"<<vec2.getY();
        //qDebug()<<vec2.getX()<<vec2.getY();
    }*/

    sf::Vector2u windowSize(1200,800);

    GameEngine engine(windowSize.x,windowSize.y,"myEngine");
    //engine.setWindowSize(windowSize.x,windowSize.y);

    GameObject *myPlayer = new GameObject();
    KeyController *playerKeyController = new KeyController(sf::Keyboard::A,
                                                           sf::Keyboard::D,
                                                           sf::Keyboard::W,
                                                           sf::Keyboard::S);
   // GravityController *playerGravityController = new GravityController(9.81);
    CircleCollider *playerCollider = new CircleCollider();
    Painter *playerPainter = new Painter();
    playerPainter->loadFromFile(texturePath+"Player2.png");


    myPlayer->addController(playerKeyController);
    //myPlayer->addController(playerGravityController);
    myPlayer->addCollider(playerCollider);
    myPlayer->setPos(0,0);
    myPlayer->addPainter(playerPainter);
    myPlayer->setSize(50,50);
    myPlayer->setDensity(1);

    /*GameObject* block = new GameObject();
    block->addCollider(new CircleCollider());
    block->addPainter(new Painter());
    block->setPos(100,100);

    engine.addGameObject(block);*/



    generateGround(&engine,30);
    generateObsticles(&engine,10,50);
    generateWall(&engine, 100,0,windowSize.y,30);
    generateWall(&engine, 100,windowSize.x-30,windowSize.y,30);

    engine.addGameObject(myPlayer);

    engine.setTickInterval(0.000);
    engine.setSimulationsTimeMultiplyer(1);
    engine.setDisplayInterval(0.05);
    engine.set_userTimer_1_enable(true);
    engine.set_userTimer_1(0.1);
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
void GameEngine::user_displayLoop()
{

}
void GameEngine::user_loop_timer_1()
{
    for(size_t i=0; i<particleList.size(); i++)
    {
        Vector vel = particleList[i]->getVelocity();
        double speed = vel.getLength()*200;
        double red = speed;
        double blue = 255.f - speed;
        if(red > 255)
            red = 255;
        if(blue > 255)
            blue = 255;
       // qDebug() << "speed: "<<speed;
        particleList[i]->setColor(sf::Color(red,0,blue));
    }
   //qDebug() << " user_loop_timer_1";
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


void generateObsticles(GameEngine *engine, unsigned int amountX,unsigned int amountY)
{
    Vector tileSize;
    sf::Vector2u windowSize = engine->getWindowSize();
    double xOffset = 300;
    double yOffset = 300;
    double size = 6;
    int counter = 0;
    particleList.reserve(amountX*amountY);
    for(unsigned int x=0; x<amountX; x++)
    {
        for(unsigned int y=0; y<amountY; y++)
        {
            tileSize.setX(size);
            tileSize.setY(tileSize.getX());
            RectCollider *collider = new RectCollider();
            Painter *painter = new Painter;
           // painter->loadFromFile(texturePath+"Obsticle.png");
            //GravityController *controller = new GravityController(9.81);

            GameObject *obj = new GameObject();
            //obj->addController(controller);
            obj->addCollider(collider);
            obj->addPainter(painter);
            //obj->setPos(i*tileSize.getX(),windowSize.y-tileSize.getY());
            obj->setSize(tileSize);
            // obj->setPos(rand()%windowSize.x,(rand()%windowSize.y));
            obj->setPos(xOffset+x*(size+1),-(yOffset+y*(size+1)));
            //obj->setVelocity(Vector((rand()%3141)/(double)1000,(rand()%1000)/(double)10));
            obj->setDensity(0.0001);

            engine->addGameObject(obj);
            particleList.push_back(obj);
            counter++;

        }
    }

}
void generateGround(GameEngine *engine, unsigned int tiles)
{
    Vector tileSize;
    sf::Vector2u windowSize = engine->getWindowSize();
    //tileSize.setX(windowSize.x/(double)tiles);
    tileSize.setX(windowSize.x);
    tileSize.setY(windowSize.x/(double)tiles);
    for(unsigned int i=0; i<1; i++)
    {
        CircleCollider *collider = new CircleCollider();
        Painter *painter = new Painter;
        painter->loadFromFile(texturePath+"Ground.png");

        GameObject *obj = new GameObject();
        obj->addCollider(collider);
        obj->addPainter(painter);
        obj->setPos(i*tileSize.getX(),-(windowSize.y-tileSize.getY()));
        obj->setSize(tileSize);
        obj->setStatic(true);


        engine->addGameObject(obj);
    }
    for(unsigned int i=0; i<1; i++)
    {
        CircleCollider *collider = new CircleCollider();
        Painter *painter = new Painter;
        painter->loadFromFile(texturePath+"Ground.png");

        GameObject *obj = new GameObject();
        obj->addCollider(collider);
        obj->addPainter(painter);
        obj->setPos(i*tileSize.getX(),0);
        obj->setSize(tileSize);
        obj->setStatic(true);


        engine->addGameObject(obj);
    }
}
void generateWall(GameEngine *engine, unsigned int tiles,double posX,double posY,int size)
{
    Vector tileSize;
    //tileSize.setX(windowSize.x/(double)tiles);
    tileSize.setX(size);
    tileSize.setY(size);
    for(unsigned int i=0; i<tiles; i++)
    {
        CircleCollider *collider = new CircleCollider();
        Painter *painter = new Painter;
        painter->loadFromFile(texturePath+"Ground.png");

        GameObject *obj = new GameObject();
        obj->addCollider(collider);
        obj->addPainter(painter);
        obj->setPos(posX,-(posY-(i+1)*size));
        obj->setSize(tileSize);
        obj->setStatic(true);


        engine->addGameObject(obj);
    }
}

void vectorTest()
{
    qDebug() << "vectortest begin";
    Vector OV1;
    Vector V1;
    Vector Vr1;

    Vector OV2;
    Vector V2;
    Vector Vr2;

    OV1.setX(5);
    OV1.setY(0);
    V1.setX(0);
    V1.setY(0);
    Vr1.setX(1);
    Vr1.setY(0);

    OV2.setX(0);
    OV2.setY(0);
    V2.setX(16);
    V2.setY(8);
    Vr2 = Vr1;

    VectorFunction func1;
    func1.setBase(OV1);
    func1.setDirection(V1);

    VectorFunction func2;
    func2.setBase(OV2);
    func2.setDirection(V2);

    double ov1x = OV1.getX();
    double ov1y = OV1.getY();
    double v1x  = V1.getX();
    double v1y  = V1.getY();

    double ov2x = OV2.getX();
    double ov2y = OV2.getY();
    double v2x  = V2.getX();
    double v2y  = V2.getY();

    Timer timer;
    timer.start(1000);
    double t1 = 0;
    double t2 = 0;
    double length;

    length = Vr1.getLength() + Vr2.getLength();

    double discriminante = pow(length,2)*(pow(v1x,2)-2*v1x*v2x+pow(v1y,2)-2*v1y*v2y+pow(v2x,2)+pow(v2y,2))-pow(ov1x,2)*(pow(v1y,2)-2*v1y*v2y+pow(v2y,2))+2*ov1x*(ov1y*(v1x-v2x)+ov2x*(v1y-v2y)-ov2y*(v1x-v2x))*(v1y-v2y)-pow(ov1y,2)*(pow(v1x,2)-2*v1x*v2x+pow(v2x,2))-2*ov1y*(ov2x*(v1y-v2y)-ov2y*(v1x-v2x))*(v1x-v2x)-pow(ov2x,2)*(pow(v1y,2)-2*v1y*v2y+pow(v2y,2))+2*ov2x*ov2y*(v1x-v2x)*(v1y-v2y)-pow(ov2y,2)*(pow(v1x,2)-2*v1x*v2x+pow(v2x,2));
    double divider = (pow(v1x,2)-2*v1x*v2x+pow(v1y,2)-2*v1y*v2y+pow(v2x,2)+pow(v2y,2));

    if(discriminante < 0 || divider == 0)
    {
        // no Collision
        qDebug() << "no result: discriminante = "<<discriminante << "\tdivider = "<<divider;
    }
    else
    {
        t1=((  sqrt(discriminante)-ov1x*(v1x-v2x)-ov1y*(v1y-v2y)+ov2x*(v1x-v2x)+ov2y*(v1y-v2y))   /  divider);
        t2=((-(sqrt(discriminante)+ov1x*(v1x-v2x)+ov1y*(v1y-v2y)-ov2x*(v1x-v2x)-ov2y*(v1y-v2y)))  /  divider);
    }
    //Sleep(10);
    timer.update();


    qDebug() << "Function1:\tOV1x\tOV1y \t\tFunction2:\tOV2x\tOV2y";
    qDebug() << "\t"<<0 << "\t" << 0 << "\t\t\t" << 0 << "\t" << 0;
    qDebug() << "\t"<<OV1.getX() << "\t" << OV1.getY() << "\t\t\t" << OV2.getX() << "\t" << OV2.getY();
    qDebug() << "\t"<<func1.getPoint(1).getX() << "\t"<<func1.getPoint(1).getY() << "\t\t\t"<<func2.getPoint(1).getX() << "\t"<<func2.getPoint(1).getY();
    qDebug() << "";


    qDebug() << "t1 = "<< t1;
    qDebug() << "t2 = "<< t2;
    qDebug() << "minDistance: \t"<<length;
    qDebug() << "t\t\tX1\tY1\t\tX2\tY2\t\tdistance\t\t";

    double deltaIterator = (double)1/(double)30;
    double t = 0.0;

    std::vector<std::vector<double> > Vr1List;
    std::vector<std::vector<double> > Vr2List;
    std::vector<std::vector<double> > VdRestList;

    for(int i=0; i<30; i++)
    {

        Vector fPos1 = func1.getPoint(t);
        Vector fPos2 = func2.getPoint(t);
        Vector Vd = fPos2 - fPos1;


        Vr1.setAngle(Vd.getAngle());
        Vr2.setAngle(M_PI + Vd.getAngle());

        Vector VdRest = Vd - Vr1 + Vr2;

        qDebug() << t << "\t\t" <<
                    fPos1.getX() << "\t"<< fPos1.getY() << "\t\t" <<
                    fPos2.getX() << "\t"<< fPos2.getY() << "\t\t" <<
                    VdRest.getLength() << "\t\t"<<
                    (fPos1+Vr1).getX() << "\t" <<(fPos1+Vr1).getY() << "\t"<<
                    (fPos2+Vr2).getX() << "\t" <<(fPos2+Vr2).getY();

        Vr1List.push_back({(fPos1).getX(),(fPos1).getY()});
        Vr1List.push_back({(fPos1+Vr1).getX(),(fPos1+Vr1).getY()});

        Vr2List.push_back({(fPos2).getX(),(fPos2).getY()});
        Vr2List.push_back({(fPos2+Vr2).getX(),(fPos2+Vr2).getY()});

        VdRestList.push_back({(fPos1+Vr1).getX(),(fPos1+Vr1).getY()});
        VdRestList.push_back({(fPos1+Vr1+VdRest).getX(),(fPos1+Vr1+VdRest).getY()});

        t+=deltaIterator;

    }
    qDebug() << "Vr1x\tVr1y\tVr2x\tVr2y\tVdRestX\tVdRestY";
    for(unsigned int i=0; i<Vr1List.size(); i++)
    {
        qDebug() << Vr1List[i][0]    << "\t"<<Vr1List[i][1] << "\t" <<
                    Vr2List[i][0]    << "\t"<<Vr2List[i][1] << "\t" <<
                    VdRestList[i][0] << "\t"<<VdRestList[i][1];
    }
    qDebug() << "timer time: "<< timer.getTime();

    qDebug() << "vectortest end";
}
