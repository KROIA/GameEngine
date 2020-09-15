#ifndef  GAMEOBJECT_H
#define  GAMEOBJECT_H
#include "EngineBase.h"

#include "collider.h"
#include "painter.h"
#include "controller.h"

class GameObject
{
public:
    GameObject();

    ~GameObject();

    void update();


    void updateSettings();

    Controller *getController();

    static vector<GameObject*>  gameObject_list;
private:
    unsigned int m_ID; // index of instance.

    void event_onCollision(Collider *collider);


    bool skipUpdateSettings;


    coordinate m_lastPos;


    Collider m_collider; // Objekt, welches das Event auslöst
    Painter  m_painter;
    Controller m_controller;


};
#endif
