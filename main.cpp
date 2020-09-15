#include "mainwindow.h"
#include <QApplication>
#include "GameEngine.h"
#include <windows.h>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    GameEngine engine;

    Velocity V1 {.velocity=1.0,.direction=coordinateF{4,0}};
    Velocity V2 {.velocity=1.0,.direction=coordinateF{0,5}};

    Velocity V3 = Physics::velocity_add(V1,V2);
    qDebug() << "V3: v="<<V3.velocity<<" dir: x="<<V3.direction.x<<" y="<<V3.direction.y;

    while(engine.isRunning())
    {
        engine.update();
    }
    w.close();
    a.exit();
    return 0;
}
