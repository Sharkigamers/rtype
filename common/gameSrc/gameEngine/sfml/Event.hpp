/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Event
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <SFML/Window.hpp>

#include "IEvent.hpp"

namespace rtype {
    namespace common {

        /* Event Class */

        class Event : public IEvent {
            public:
                Event()
                {};
                ~Event() noexcept = default;

                bool isMousePressed() const noexcept final
                {
                    if (_event.type == sf::Event::MouseButtonPressed)
                        return true;
                    return false;
                }
                
                bool isTextEntered() const noexcept final
                {
                    if (_event.type == sf::Event::TextEntered)
                        return true;
                    return false;
                }

                unsigned int characterEntered() const noexcept final
                {
                    return _event.text.unicode;
                }

                bool isMouseReleased() const noexcept final
                {
                    if (_event.type == sf::Event::MouseButtonReleased)
                        return true;
                    return false;
                }

                bool isKeyPressed() const noexcept final
                {
                    if (_event.type == sf::Event::KeyPressed)
                        return true;
                    return false;
                }

                bool isKeyReleased() const noexcept final
                {
                    if (_event.type == sf::Event::KeyReleased)
                        return true;
                    return false;
                }

                char eventKeyCode() const noexcept final
                {
                    return _event.key.code;
                }

                bool compareCharWithEventKeyCode(char const &key) const noexcept final
                {
                    if (eventKeyCode() == key)
                        return true;
                    return false;
                }

                bool isEscapePressed() const noexcept final
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        return true;
                    }
                    return false;
                }

                bool isClosing() const noexcept final
                {
                    if (_event.type == sf::Event::Closed)
                        return true;
                    return false;
                }

                sf::Event &getEvent()
                {
                    return _event;
                }

                void setEvent(sf::Event &event)
                {
                    _event = event;
                }

            protected:
            private:
                sf::Event _event;
        };
    }
}

#endif /* !EVENT_HPP_ */
