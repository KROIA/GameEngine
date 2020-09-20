#ifndef EngineMisc_H
#define EngineMisc_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <QDebug>

#include <windows.h>
#include <chrono>
#include <thread>

#include "timer.h"



using std::string;
using std::vector;

typedef sf::Vector2<double> coordinateF;
typedef sf::Vector2<int> coordinate;
typedef sf::Vector2<unsigned int> coordinateU;

#define TYPE_TAG_COLLIDER 0
class Collider;

#define TYPE_TAG_GAMEOBJECT 1
class GameObject;

#define TYPE_TAG_CONTROLLER 2
class Controller;

#define TYPE_TAG_PAINTER 3
class Painter;


namespace EngineMisc
{
    extern coordinate mapSize;
    extern coordinate graphicScale;

    extern double framesPerSecond;
    extern double framesPerSecondTarget;
    extern double updateDurationTime; //sec

    extern double physicsTicksPerSecond;

    extern unsigned long long sycle;
    extern unsigned long long tmpSycleCounter;


    struct __deleteTarget
    {
        int typeTag;
        unsigned int ID;
    };


    extern bool checkOutOfBoarder(coordinate coord);

    extern vector<__deleteTarget> __deleteTargetList;
    extern void __deleteLater(int typeTag,unsigned int ID);


};

struct Velocity{
    double     velocity; // m/s
    coordinateF direction;
};
struct Force{
    double     force; // N
    coordinateF direction;
};


#endif // EngineMisc_H
