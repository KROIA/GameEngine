#ifndef KEYCONTROLLER_H
#define KEYCONTROLLER_H

#include "controller.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>

class KeyController : public Controller
{
    public:
        KeyController(sf::Keyboard::Key keyLeft,
                      sf::Keyboard::Key keyRight,
                      sf::Keyboard::Key keyUp,
                      sf::Keyboard::Key keyDown);
        KeyController(const KeyController &controller);
        virtual ~KeyController();

        virtual void tick(double timeInterval);

    protected:
        //void handleKeyEvent(sf::Event &event);
        void handleKeyPress();

    private:
        Vector m_leftMove;
        Vector m_rightMove;
        Vector m_upMove;
        Vector m_downMove;

        sf::Keyboard::Key m_keyLeft;
        sf::Keyboard::Key m_keyRight;
        sf::Keyboard::Key m_keyUp;
        sf::Keyboard::Key m_keyDown;
};

#endif
