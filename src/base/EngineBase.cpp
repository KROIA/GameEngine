#include "EngineBase.h"

namespace EngineBase
{
    coordinate mapSize;
    coordinate graphicScale;

    double framesPerSecond = 1;
    double framesPerSecondTarget = 60;
    double updateDurationTime = 0.001;

    unsigned long long sycle = 0;
    unsigned long long tmpSycleCounter = 0;


    bool checkOutOfBoarder(coordinate coord)
    {
        bool outOfBoarder = false;
        if(coord.x < 0 || coord.y < 0)
           outOfBoarder = true;
        if(coord.x > mapSize.x || coord.y > mapSize.y)
            outOfBoarder = true;
        if(outOfBoarder)
        {
            qDebug() << "Error: Out of boarder!";
        }
        return outOfBoarder;
    }

    vector<__deleteTarget> __deleteTargetList;
    void __deleteLater(int typeTag,unsigned int ID)
    {
        return;
        __deleteTargetList.push_back(__deleteTarget{.typeTag = typeTag,.ID=ID});
        switch(typeTag)
        {
            case TYPE_TAG_COLLIDER:
            {
                qDebug() << "Delete later: TypeTag: "<<typeTag<<"\t ID: "<<ID << "\t Type: Collider";
                break;
            }
            case TYPE_TAG_GAMEOBJECT:
            {
                qDebug() << "Delete later: TypeTag: "<<typeTag<<"\t ID: "<<ID << "\t Type: GameObject";
                break;
            }
            case TYPE_TAG_CONTROLLER:
            {
                qDebug() << "Delete later: TypeTag: "<<typeTag<<"\t ID: "<<ID << "\t Type: Controller";
                break;
            }
        }
    }

};



