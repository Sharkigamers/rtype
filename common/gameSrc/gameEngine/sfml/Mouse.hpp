/*
** EPITECH PROJECT, 2020
** B-CPP-501-PAR-5-1-rtype-emmanuel.blineau
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include <SFML/Window.hpp>

#include "IMouse.hpp"

namespace rtype {
    namespace common {

        /* Mouse Class */

        class Mouse : public IMouse {
            public:
                static const char LEFT = 0;
                static const char MIDDLE = 1;
                static const char RIGHT = 2;

            public:
                Mouse() = default;
                ~Mouse() noexcept = default;

                bool buttonMousePressed(char const &button) noexcept final
                {
                    switch (button)
                    {
                    case 0:
                        return _mouse.isButtonPressed(sf::Mouse::Button::Left);
                        break;
                    case 1:
                        return _mouse.isButtonPressed(sf::Mouse::Button::Middle);
                        break;
                    case 2:
                        return _mouse.isButtonPressed(sf::Mouse::Button::Right);
                        break;
                    default:
                        break;
                    }
                    return false;
                }

                void setMousePosition(float const &x, float const &y) noexcept final
                {
                    _mouse.setPosition(sf::Vector2i(x, y));
                }

                std::pair<float, float>getMousePosition() noexcept final
                {
                    return std::make_pair(_mouse.getPosition().x, _mouse.getPosition().y);
                }

            protected:
            private:
                sf::Mouse _mouse;
        };
    }
}

#endif /* !MOUSE_HPP_ */
