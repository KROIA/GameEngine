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



    while(engine.isRunning())
    {
        engine.update();
    }
    w.close();
    a.exit();
    return 0;
}
