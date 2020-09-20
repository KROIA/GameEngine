#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "EngineMisc.h"
#include "physics.h"

#include "gameObject.h"

#include <QDebug>

class GameEngine
{
public:
    GameEngine();

    ~GameEngine();

    // Window
    void setWindowSize(coordinateU windowSize);
    void setWindowName(string name);
    void close();
    bool isRunning();

    // Game
    void update();      // Updates one gametick



    void setMapSize(coordinate mapsize);

    // Graphics
    void setBackgroundColor(sf::Color color);



private:
    void checkCollision();
    void calculatePhysics();

    // Window
    void updateSettings();
    bool m_settingsSkipUpdate;
    coordinateU m_windowSize; // Windowsize (width = x)
    string m_windowName;                    //
    sf::RenderWindow *m_renderWindow;       // SFML Window Object
    bool m_isRunning;
    // Boarder
    vector<Collider*> m_boarder;

    // Events
    void handleEvent();
    void handleKeyEvent(sf::Event &event);


    // Gamesettings
    coordinate m_mapSize;    // Size of the gameWorld



    // Graphics
    void updateGraphics();
    coordinate  m_graphicsScale;
    sf::Texture m_backgroundTexture;        // Background pixelmap
    sf::Image   m_backgroundImage;          //
    sf::Sprite  m_backgroundSprite;         //
    sf::Color   m_backgroundColor;          //

    GameObject m_object;
    GameObject m_object_2;
    GameObject m_ground;

    //Timing
    Timer m_frameUpdateTimer;
    Timer m_physicsUpdateTimer;
    std::chrono::high_resolution_clock::time_point m_timer1_start;
    std::chrono::high_resolution_clock::time_point m_timer1_end;
    std::chrono::duration<double> m_time1_span;

    // Garbagehandle
    static void __deleteTargets();
};

#endif // GAMEENGINE_H
