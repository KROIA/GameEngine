#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <windows.h>
#include <iostream>
#include <stdio.h>

#include <SFML/Graphics.hpp>
#include "timer.h"
#include "vector.h"
#include "vectorFunction.h"

#include "gameObject.h"

#include <QDebug>

class GameEngine
{
    public:
        GameEngine(unsigned int width, unsigned int height,const std::string &windowname);
        virtual ~GameEngine();

        virtual void start();
        virtual void stop();

        static void user_loop();        // is called as often as possible
        static void user_tickLoop();    // is called once a tick (before the engine calculates the next tick)
        static void user_loop_timer_1();// is called depending on its time
        static void user_loop_timer_2();// ...
        static void user_loop_timer_3();// ...
        static void user_loop_timer_4();// ...
        static void user_loop_timer_5();// ...

        virtual void setWindowSize(unsigned int width,unsigned int height);
        virtual sf::Vector2u getWindowSize() const;
        virtual void setWindowName(const std::string &name);
        virtual std::string getWindowName() const;
        virtual void setBackgroundColor(sf::Color color);
        virtual void setTickInterval(double sec);
        virtual void setDisplayInterval(double sec);
        virtual void set_userTimer_1(double sec);
        virtual void set_userTimer_2(double sec);
        virtual void set_userTimer_3(double sec);
        virtual void set_userTimer_4(double sec);
        virtual void set_userTimer_5(double sec);
        virtual void set_userTimer_1_enable(bool enable);
        virtual void set_userTimer_2_enable(bool enable);
        virtual void set_userTimer_3_enable(bool enable);
        virtual void set_userTimer_4_enable(bool enable);
        virtual void set_userTimer_5_enable(bool enable);

        virtual unsigned long long getCurrentTick() const;
        virtual double getTickUpdateTime() const;

        virtual void addGameObject(GameObject *obj);
        virtual void setSimulationsTimeMultiplyer(double factor);



    protected:

        virtual void tick();
        virtual void move();
        virtual void checkCollision();
        virtual void draw();
        virtual void handleEvents();

        virtual void handleUserTimer();
        virtual bool isInFrame(GameObject *obj);



        bool m_engineRunning;
        Timer m_userTimer_1; double m_userTimer_1_Interval; bool m_userTimer_1_enable;
        Timer m_userTimer_2; double m_userTimer_2_Interval; bool m_userTimer_2_enable;
        Timer m_userTimer_3; double m_userTimer_3_Interval; bool m_userTimer_3_enable;
        Timer m_userTimer_4; double m_userTimer_4_Interval; bool m_userTimer_4_enable;
        Timer m_userTimer_5; double m_userTimer_5_Interval; bool m_userTimer_5_enable;

        Timer m_tickTimer; double m_tickInterval;
        Timer m_displayTimer; double m_displayInterval;
        double m_simulationsTimeMultiplyer;
        double m_simulationsTimeInterval;

        sf::RenderWindow *m_renderWindow;
        sf::View m_windowView;
        sf::Vector2u m_windowSize;
        std::string m_windowName;
        sf::Color m_backgroundColor;

        std::vector<GameObject*> m_gameObjectList;

    private:
        unsigned long long m_currentTick;


};
#endif
